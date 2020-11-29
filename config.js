var config = module.exports = {}

config._app = {
    port: process.env.PORT || '3000',
    ip: process.env.IP || 'localhost',
}

config.mongo = {
    port: process.env.MONGODB_DB_PORT || '27017',
    uri: `mongodb://${config._app.ip}:${process.env.MONGODB_DB_PORT || '27017'}/`,
    db: 'sensors',
    user: ''
}