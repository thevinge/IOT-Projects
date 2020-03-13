var express = require('express');
var router = express.Router();
var db = require('../database');

router.post('/create', function(req, res, next) {
    let name = req.body.name;
    db.one("INSERT INTO tuser (name) values ($1) RETURNING id,name", name)
        .timeout()
        .then(data => {
            res.status(200).json(data);
        })
        .catch(err => {
            res.status(500).send(err)
        });
});



router.post('/', function(req, res, next) {
    console.table(req.body);
    let temp = req.body.temp;
    let light = req.body.light;
    let reqno = req.body.reqno;
    console.table({temp, light, reqno});
    console.table(db);
    db.none("INSERT INTO tiot (temp,light,reqno) values ($1, $2, $3)", [temp, light, reqno])
        .then(() => {
            console.log("got here 1?");
            res.status(200).send();
        })
        .catch(err => {
            console.log("got here 2?");
            res.status(500).send(err)
        });
    console.log("got here 3?");
});


module.exports = router;