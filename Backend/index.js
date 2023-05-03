const express = require("express");
const cors = require("cors");
const bodyparser = require("body-parser");
const cookieparser = require("cookie-parser");
const session = require("express-session");
const createModule = require("./RogersRamanujanCounter.js");

require("dotenv").config();

const app = express();

app.use(express.json());
app.use(cors({
  origin: ["http://localhost:3000"],
  methods: ["GET", "POST"],
  credentials: true,
}));

app.use(cookieparser());
app.use(bodyparser.urlencoded({ extended: true }));

app.use(session({
  key: "userId",
  secret: "ENS492Project",
  resave: false,
  saveUninitialized: false,
  cookie: {
    expires: 60 * 60 * 24,
  },
}));

app.listen(process.env.PORT || 3001, () => {
  console.log('The application is running on localhost:3001!');
});

app.post("/RogersRamanujanCounter",(req,res) =>{
    const mValue = req.body.mValue;
    const nValue = req.body.nValue;
    const kValue = 2;
  
    createModule().then(({RogersRamanujanCounter}) => {
        // Perform computation
        const rogersramanujancounter = new RogersRamanujanCounter();
        const root = rogersramanujancounter.rrgc(mValue, nValue, kValue);

        console.log(root);
        res.send({message: root});
     });
})

app.post("/RogersRamanujanGordonCounter",(req,res) =>{
  const mValue = req.body.mValue;
  const nValue = req.body.nValue;
  const kValue = req.body.kValue;

  createModule().then(({RogersRamanujanCounter}) => {
      // Perform computation
      const rogersramanujancounter = new RogersRamanujanCounter();
      const root = rogersramanujancounter.rrgc(mValue, nValue, kValue);

      console.log(root);
      res.send({message: root});
   });
})

app.post("/RogersRamanujanEnumeration",(req,res) =>{
  const mValue = req.body.mValue;
  const nValue = req.body.nValue;
  const kValue = 2;

  createModule().then(({RogersRamanujanCounter}) => {
      // Perform computation
      const rogersramanujancounter = new RogersRamanujanCounter();
      rogersramanujancounter.rr(mValue, nValue, kValue);
      const root = rogersramanujancounter.getPartnum();
      const data = rogersramanujancounter.getPartitions();
  
      console.log(root);
      res.send({message: root, data: data});
   });
})

app.post("/RogersRamanujanGordonEnumeration",(req,res) =>{
const mValue = req.body.mValue;
const nValue = req.body.nValue;
const kValue = req.body.kValue;

createModule().then(({RogersRamanujanCounter}) => {
    // Perform computation
    const rogersramanujancounter = new RogersRamanujanCounter();
    rogersramanujancounter.rr(mValue, nValue, kValue);
    const root = rogersramanujancounter.getPartnum();
    const data = rogersramanujancounter.getPartitions();

    console.log(root);
    res.send({message: root, data: data});
 });
})
