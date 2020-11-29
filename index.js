const express = require('express')
const mongoose = require('mongoose')
const bodyParser = require('body-parser')
const methodOverride = require('method-override')
const sensorController = require('./controllers/sensor')
const { _app, mongo } = require('./config')
const app = express()

const mongodbURL = `mongodb+srv://${mongo.user}:${mongo.password}@${mongo.uri}/${mongo.db}?retryWrites=true&w=majority`

mongoose.connect(mongodbURL, { useNewUrlParser: true, useUnifiedTopology: true }, (err, res) => {
    if (err) throw err
    console.log('Connected to Database: ' + mongo.db)
})

app.use(bodyParser.urlencoded({ extended: true }))
app.use(bodyParser.json())
app.use(methodOverride())

const api_router = express.Router()

api_router.route('/sensors/data')
    .post(sensorController.addData)

app.use('/api', api_router)

app.listen(_app.port, () => {
    console.log(`App listening at http://localhost:${_app.port}`)
})