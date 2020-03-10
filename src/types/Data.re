type t = {
  questions: array(Question.t),
  links: array(string),
};

let make = (questions, links) => {questions, links};

let decode = json => {
  make(json##questions, json##links);
};

let questions = t => t.questions;
