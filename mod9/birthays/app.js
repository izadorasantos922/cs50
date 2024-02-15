const express = require("express");
const exphbs = require("express-handlebars");
const conn = require("./db/conn")
const app = express();
const PORT = 3000;
app.engine('handlebars', exphbs.engine());
app.set('view engine', 'handlebars');
app.use(express.static('public'))
app.use(express.urlencoded({
    extended: true
}));


app.get("/", (req, res)=>{
    const query = 'SELECT * FROM birthday'
    conn.query(query, function(err, data){
        if(err){
            console.log(err)
            return
        }
        const birthdays = data
        res.render('./layouts/birthdayform', {birthdays})
    })
})

app.post("/addbirthday", (req, res) => {
    const name = req.body.name;
    const mouth = req.body.mouth;
    const day = req.body.day;
    const query = 'INSERT INTO birthday (birthday_person, mouth, birthday_day) VALUES (?, ?, ?)';
    const values = [name, mouth, day];

    conn.query(query, values, function(err) {
        if (err) {
            console.log(err);
            return;
        }
        res.redirect('/');
    });
});


conn.connect(function(err){
    if(err){
        console.log(err)
        return
    }
    console.log("Connected")
    app.listen(PORT, () => {
        console.log(`Server is running on port ${PORT}`);})
})