const router = require("express").Router();
const multer = require("multer");
var uploads = multer({ dest: "../uploads" });
const shell = require("shelljs");
require("dotenv").config();
var fs = require("fs-extra");
const ocrSpaceApi = require("ocr-space-api"); //Calling the Ocr.Space API
const { check } = require("fontawesome");

// OCR.space setting default options 
var options = {
  apikey: "K87590356888957",
  language: "eng", // English as default language
  imageFormat: "image/png", // Image Type (Only png or jpeg supported)
  isOverlayRequired: true,
};
 
// Creating a post request to upload file and process via OCR 
router.post("/", uploads.single("file"), (req, res, next) => {
  if (req.file === undefined) {
    var err = new Error("Error!! No File Found!!"); // Checks for file, and handles error
    next(err);
  } 
  fs.renameSync(req.file.path, "/tmp/uploads/temp"); //Renaming the file to temp
 
  let filepath = "tmp/uploads/temp";

  // Run and wait the result 
  ocrSpaceApi 
    .parseImageFromLocalFile(filepath, options)
    .then(async function (parsedResult) {
      const detections = parsedResult.parsedText;
      let text = detections.toLowerCase(); //Converting text to Lowercase
      console.log(text);
      shell.cd("./Trie"); // Changing directory to ./Trie
      await fs.writeFileSync("ocrData.txt", text);
  
      // shell.exec("g++ -std=c++11 checker.cpp -o checker");
      // var cmmnd = `.\checker`  
      var data = shell.exec("checker ocrData.txt").toString();   //Driver code for Executing program and returning result using Tries
      var array = data.split("\n");
      if (array.length <= 1)
        return res.send("Some problem occurred <a href='/'> Go back!</a>"); //If error, return to index
      res.render("display", { data: array, text, tone: null });
    })
    .catch(function (err) {
      console.log("ERROR:", err);
    }); 
});

module.exports = router;
