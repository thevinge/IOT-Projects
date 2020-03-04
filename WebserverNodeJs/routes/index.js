var express = require('express');
var router = express.Router();

const fs = require('fs');


/* GET home page. */
router.get('/get', function(req, res, next) {
    console.log(req.body)
});


module.exports = router;
