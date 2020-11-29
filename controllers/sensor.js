const Data = require('../models/data')

exports.addData = (req, res) => {

    var data = new Data({
        sensorName: req.body.sensorName,
        measures: req.body.measures
    })

    data.save((err, data) => {
        if (err) return res.send(500, err)        
        res.status(201).jsonp(data)
    })
}
