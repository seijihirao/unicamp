const express = require('express')

var app = express()

app.get('/', (req, res) => {
    res.send('<html style="background-color: pink;"><h1>Hello Darkness My Old Friend</h1></html>')
})

app.get('/about', (req, res) => {
    res.send('<html style="background-color: purple;"><h1>:)</h1></html>')
})

app.get('/badrequest', (req, res) => {
    res.send('<html style="background-color: red;"><h1>OH NO</h1></html>')
})

app.listen(8080, () => {
    console.log('Server Running')
})
