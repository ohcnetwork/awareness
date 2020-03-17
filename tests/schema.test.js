const chai = require('chai');
const schema = require("../src/components/dataSchema.json");

chai.use(require('chai-json-schema'));
const expect = chai.expect;

const data = (function(){
  const fs = require('fs');
  const stripJsonComments = require('strip-json-comments');
  const text = fs.readFileSync("src/components/data.json").toString();
  return JSON.parse(stripJsonComments(text));
})()

describe("Data", function() {
  it("should be properly validated by the json schema", function() {
    expect(data).to.be.jsonSchema(schema);
  });
});