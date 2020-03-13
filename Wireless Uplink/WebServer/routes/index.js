var express = require('express');
var router = express.Router();
var db = require('..\\database');

router.post('/create', function(req, res, next) {
    let name = req.body.name;
    db.one("INSERT INTO tuser (name) values ($1) RETURNING id,name", name)
        .then(data => {
            res.status(200).json(data);
        })
        .catch(err => {
            res.status(500).send(err)
        });
});

module.exports = router;