var config = module.exports = {}

config._app = {
    port: process.env.PORT || '3000',
    ip: process.env.IP || 'localhost',
}

config.mongo = {
    uri: process.env.MONGO_URI,
    db: process.env.MONGO_DB,
    user: process.env.MONGO_USER,
    password: process.env.MONGO_PASSWORD
}