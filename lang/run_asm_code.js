lang = require("./asm_build/lang.js");

function run_string(code_string) {
    var buffer = lang._malloc(code_string.length + 1);
    lang.stringToUTF8(code_string, buffer, code_string.length + 1);
    lang._run_code_string(buffer);
}

var filename = process.argv[2];
if (filename == undefined) {
    throw Error("Provide code file");
}

var fs = require('fs');
fs.readFile(filename, 'utf8', function(err, contents) {
    run_string(contents);
});