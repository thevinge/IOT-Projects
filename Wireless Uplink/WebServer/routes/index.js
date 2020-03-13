var express = require('express');
var router = express.Router();
var db = require('..\\database');


function setup(io) {
    router.get('/', function (req, res, next) {
        res.render('index', {title: 'Express'});
    });


    router.get('/ws', function (req, res, next) {
        update(io);
        res.status(200).send();
    });


    router.get('/api/status', function (req, res, next) {
        db.many(`SELECT DISTINCT ON (userid) userid, status, dt, tuser.name FROM tevent INNER JOIN tuser AS tuser ON tevent.userid = tuser.id ORDER BY userid, dt DESC`)
            .then(data => {
                res.status(200).json(data);
            }).catch(err => {
            res.status(404).send();
        })
    });

    router.get('/api/status/:id', function (req, res, next) {
        db.one(`SELECT tevent.id, userid, status, dt, tuser.name FROM tevent INNER JOIN tuser AS tuser ON tevent.userid = tuser.id WHERE userid = $1 ORDER BY dt DESC LIMIT 1`, req.params.id)
            .then(data => {
                res.status(200).json(data);
            }).catch((err) => {
            res.status(404).send();
        })
    });

    router.post('/api/in/:id', function (req, res, next) {
        insertEvent(req, status.IN)
            .then(data => {
                res.status(200).json(data);
                update(io);
            })
            .catch((err) => {
                console.log(err);
                res.status(500).send(err);
            });
    });

    router.post('/api/out/:id', function (req, res, next) {
        insertEvent(req, status.OUT)
            .then(data => {
                res.status(200).json(data);
                update(io);
            })
            .catch((err) => {
                console.log(err);
                res.status(500).send(err);
            });
    });

    return router;

}

function update(io){
    getStatus().then(data => {
        io.emit("update", data );
    });
}

function getStatus(){
   return db.many(`SELECT DISTINCT ON (userid) userid, status, dt, tuser.name FROM tevent INNER JOIN tuser AS tuser ON tevent.userid = tuser.id ORDER BY userid, dt DESC`)
}

function insertEvent(req, status) {
    return db.one(`INSERT INTO tevent (userid, status) VALUES ($1,'${status}') RETURNING *`, req.params.id)
}

module.exports.setup = setup;

const status = {
    IN: "IN",
    OUT: "OUT"
};
