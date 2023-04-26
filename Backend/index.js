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
/* 
app.post("/test", (req, res) => {
    const initial_guess = req.body.initial_guess;
    const tolerance = req.body.tolerance;

    createModule().then(({ NewtonRaphson }) => {
        // Perform computation
        const newtonraphson = new NewtonRaphson(tolerance);
        const root = newtonraphson.solve(initial_guess);

        console.log(root);
        res.send({ message: root });
    });
})
*/

app.post("/test",(req,res) =>{
    const mValue = req.body.mValue;
    const nValue = req.body.nValue;
  
    createModule().then(({RogersRamanujanCounter}) => {
        // Perform computation
        const rogersramanujancounter = new RogersRamanujanCounter();
        const root = rogersramanujancounter.rrgc(mValue, nValue);

        console.log(root);
        res.send({message: root});
     });
})

