const mongoose = require('mongoose')

const MeasureSchema = new mongoose.Schema({
    name: String,
    value: Number,
    units: String
})

const DataSchema = new mongoose.Schema({
    sensorName: String,
    created: { type: Date, default: Date.now },
    measures: [MeasureSchema]
})

module.exports = mongoose.model('Data', DataSchema, 'data')
