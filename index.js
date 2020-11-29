const express = require('express')
var bodyParser = require('body-parser')
var methodOverride = require('method-override')
var sensorController = require('./controllers/sensor')

const app = express()
const port = 3000

app.use(bodyParser.urlencoded({ extended: true }))
app.use(bodyParser.json())
app.use(methodOverride())

var api_router = express.Router()

api_router.route('/sensors/data')
    .post(sensorController.addData)

app.use('/api', api_router)

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
})