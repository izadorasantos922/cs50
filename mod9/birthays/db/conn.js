const mysql = require("mysql2");
const conn = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'izadora2005',
    database: 'birthays'
})

module.exports = conn