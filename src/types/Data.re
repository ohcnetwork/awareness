type t = {
  quiz: array(Quiz.t),
  links: array(string),
};

let make = (quiz, links) => {quiz, links};

let makeData = json => {
  make(json##quiz |> Quiz.makeArray, json##links);
};

let quiz = t => t.quiz;
