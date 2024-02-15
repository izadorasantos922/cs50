from flask import Flask, render_template, request, redirect, url_for, session
from werkzeug.security import generate_password_hash, check_password_hash
from bson import ObjectId
from functools import wraps
from datetime import datetime
from flask_pymongo import PyMongo
import requests

app = Flask(__name__)
app.config['MONGO_URI'] = 'mongodb://localhost:27017/finance'
app.secret_key = 'iza5869'
mongo = PyMongo(app)

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if 'user_id' not in session:
            return redirect(url_for('home'))
        return f(*args, **kwargs)
    return decorated_function

@app.route('/')
def home():
    return render_template("register.html")

@app.route('/register',methods=['POST'])
def register():
    name = request.form['name']
    passwd = request.form['password']
    confirmpasswd = request.form['comfirmpassword']
    if not name or  name.strip() == "":
        return render_template("Error.html", message="Name is missing!")
    if not passwd or passwd.strip() == "":
        return render_template("Error.html", message="Password is missing!")
    if not confirmpasswd or confirmpasswd.strip() == "":
        return render_template("Error.html", message="comfirm password is missing!")
    if confirmpasswd != passwd:
        return render_template("Error.html", message="Password and comfirm password is diferent!")
    collection = mongo.db.users
    exist_user = collection.find_one({'username': name})
    if exist_user:
        return render_template("Error.html", message="User alredy exits, go to login page")
    result = collection.insert_one({
    'username': name,
    'password': generate_password_hash(passwd),
    'cash': 10000
    })
    if result.inserted_id:
        return redirect(url_for('login'))
    else:
        return render_template("Error.html", message="Failed to register user.")

@app.route("/login", methods=["POST", "GET"])
def login():
    if request.method == "POST":
        name = request.form['name']
        passwd = request.form['password']
        collection = mongo.db.users
        exist_user = collection.find_one({'username': name})
        if exist_user:
            password = exist_user.get('password')
            if check_password_hash(password, passwd):
                session['user_id'] = str(exist_user['_id'])
                return redirect(url_for('dashboard'))
            else:
                return render_template("Error.html", message="Password is wrong, try again")  
        else: 
            return render_template("Error.html", message="User not found")  
    else:
        return render_template("login.html")
    
@app.route("/search", methods=["POST", "GET"])
@login_required
def search():
    if request.method == "POST":
        symbolname = request.form["symbol"]
        url = f"https://api.iex.cloud/v1/data/core/quote/{symbolname}?token=pk_720ac257f80f4e498b7834911d739ad5"
        response = requests.get(url)
        if response.status_code == 200:
            data = response.json()
            if type(data) is not type(None) and data[0] is not None:
                symbol_name = data[0]["symbol"] 
                dolar = data[0]["latestPrice"] 
                return render_template("searchresult.html", symbol=symbol_name, dolar=dolar)
            else: 
                return render_template("Error.html", message="Not found")
        else: 
            return render_template("Error.html", message="Not found")
    else:
        return render_template("search.html")
    
@app.route("/buy", methods=["POST", "GET"])
@login_required
def buy():
    if request.method == "POST":   
        if 'symbol' in request.form:  
            symbol_name = request.form["symbol"]
            if not symbol_name or symbol_name.strip() == "":
                return render_template("Error.html", message="Missing the symbol's name")
        else:
            return render_template("Error.html", message="Missing the symbol's name") 
        if 'qtdy' in request.form:  
            qtdystr = request.form["qtdy"]
            if not qtdystr or qtdystr.strip() == "":
                return render_template("Error.html", message="Missing the quantity")
        else:
            return render_template("Error.html", message="Missing the quantity")
        qtdy = int(qtdystr)
        if qtdy < 1:
            return render_template("Error.html", message="Quantity of shares has to be more than 0")
        
        url = f"https://api.iex.cloud/v1/data/core/quote/{symbol_name}?token=pk_720ac257f80f4e498b7834911d739ad5"
        response = requests.get(url)
        if response.status_code == 200:
            data = response.json()
            if type(data) is not type(None) and data[0] is not None:
                symbolname = data[0]["symbol"] 
                dolar = data[0]["latestPrice"] 
                total_price = dolar * qtdy
                user_id = session['user_id']
                user_id_object = ObjectId(user_id)
                user_cash = mongo.db.users.find_one({'_id': user_id_object}, {'cash': 1}).get('cash', 0)     
                if user_cash >= total_price: 
                    transactionscollection = mongo.db.transactions
                    userscollection = mongo.db.users
                    result = transactionscollection.insert_one({
                    'user_id': user_id,
                    'name': symbolname,
                    'type': 'buy',
                    'shares': qtdy,
                    'price': dolar,
                    'total': total_price,
                    'timestamp': datetime.now()
                    })
                    if result.inserted_id:
                        userscollection.update_one(
                            {"_id": ObjectId(user_id)}, 
                            {"$inc": {"cash": -total_price}})
                        return redirect(url_for('dashboard'))
                    else:
                        return render_template("Error.html", message="Failed to buy, try again later.")
                else:
                    return render_template("Error.html", message="You dont have enough money")
            else: 
                return render_template("Error.html", message="Not found try again")
        else: 
            return render_template("Error.html", message="Not found try again")
    else:
        return render_template("buy.html")

@app.route("/sell", methods=["POST", "GET"])
@login_required
def sell():
    user_id = session['user_id']
    transactions_collection = mongo.db.transactions
    consolidated_transactions = session.get('consolidated_transactions', {})
    user_transactions_list = list(consolidated_transactions.values())
    if request.method == "POST":  
        if 'symbol' in request.form:  
            symbol_name = request.form["symbol"]
        else:
            return render_template("Error.html", message="Missing the symbol")
        if 'qtdy' in request.form:  
            qtdystr = request.form["qtdy"]
            if not qtdystr or qtdystr.strip() == "":
                return render_template("Error.html", message="Missing the quantity")
        else:
            return render_template("Error.html", message="Missing the quantity")
        if qtdystr != "":
            qtdy = int(qtdystr)
        buy_transactions = [transaction["shares"] for transaction in user_transactions_list if transaction["name"] == symbol_name and transaction["type"] == "buy"]
    
        total_shares = sum(buy_transactions)
        if qtdy < 0:
            return render_template("Error.html", message="Quantity of shares has to be more than 1")
        if total_shares < qtdy:
            return render_template("Error.html", message="You dont have enough shares")
        else:
            url = f"https://api.iex.cloud/v1/data/core/quote/{symbol_name}?token=pk_720ac257f80f4e498b7834911d739ad5"
            
            response = requests.get(url)
            if response.status_code == 200:
                data = response.json()
                if type(data) is not type(None) and data[0] is not None:
                    symbolname = data[0]["symbol"] 
                    dolar = data[0]["latestPrice"] 
                    total_price = dolar * qtdy
                    userscollection = mongo.db.users
                    result = transactions_collection.insert_one({
                    'user_id': user_id,
                    'name': symbolname,
                    'type': 'sell',
                    'shares': qtdy,
                    'price': dolar,
                    'total': total_price,
                    'timestamp': datetime.now()})
                    if result.inserted_id:
                        userscollection.update_one(
                        {"_id": ObjectId(user_id)}, 
                        {"$inc": {"cash": total_price}})
                        if symbol_name in consolidated_transactions:
                            consolidated_transactions[symbol_name]["shares"] -= qtdy
                            for key, transaction in consolidated_transactions.items():
                                transaction["_id"] = str(transaction["_id"])
                            session['consolidated_transactions'] = consolidated_transactions
                        return redirect(url_for('dashboard'))
                    else:
                        return render_template("Error.html", message="Failed to sell, try again later.")
                else:
                    return render_template("Error.html", message="Not found")
            else: 
                return render_template("Error.html", message="Not found try again")
    else:
        return render_template("sell.html" , user_transactions_list=user_transactions_list)
    
@app.route("/dashboard", methods=["POST", "GET"])
@login_required
def dashboard():
    user_id = session['user_id']
    transactionscollection = mongo.db.transactions
    userscollection = mongo.db.users
    user = userscollection.find_one({"_id": ObjectId(user_id)})
    user_transactions = transactionscollection.find({"user_id": user_id})
    consolidated_transactions = {}
    for transaction in user_transactions:
        symbol = transaction["name"]
        shares = transaction["shares"] if transaction["type"] == "buy" else -transaction["shares"]

        if symbol in consolidated_transactions:
            consolidated_transactions[symbol]["shares"] += shares
        else:
            consolidated_transactions[symbol] = transaction
            consolidated_transactions[symbol]["shares"] = shares
    for key, transaction in consolidated_transactions.items():
        transaction["_id"] = str(transaction["_id"])
        transaction["total"] = transaction["shares"] * transaction["price"]
    session['consolidated_transactions'] = consolidated_transactions  
    user_transactions_list = list(consolidated_transactions.values())
    print(user_transactions_list)
    if user_transactions_list:
        total_invested = sum([t["total"] for t in user_transactions_list])
    else:
        total_invested = None
    if user and total_invested:
        return render_template("dashboard.html", user=user, transactions=user_transactions_list, total_invested=total_invested)
    elif user and not total_invested:   
        return render_template("dashboard.html", user=user, transactions=user_transactions_list)
    else:
        return render_template("Error.html", message="Not found, try again")

@app.route("/history", methods=["POST", "GET"])  
@login_required
def history():
    user_id = session['user_id']
    transactions_collection = mongo.db.transactions
    user_transactions = transactions_collection.find({"user_id": user_id})
    user_transactions_list = list(user_transactions)
    for transaction in user_transactions_list:
        transaction['formatted_timestamp'] = transaction['timestamp'].strftime('%Y-%m-%d %H:%M:%S')
    if user_transactions_list:
        return render_template("history.html",  user_transactions_list=user_transactions_list, )  
    else:
        return render_template("Error.html", message="Not found, try again")


@app.route("/logout")
def logout():
    session.pop('user_id', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
