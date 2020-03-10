type t = {
  title: string,
  path: string,
  questions: array(Question.t),
  buttonText: string,
};

let make = (~title, ~path, ~questions, ~buttonText) => {
  {title, path, questions, buttonText};
};

let title = t => t.title;
let path = t => t.path;
let questions = t => t.questions;
let buttonText = t => t.buttonText;

let makeArray = json => {
  json
  |> Array.map(a =>
       make(
         ~title=a##title,
         ~path=a##path,
         ~questions=a##questions |> Question.makeArray,
         ~buttonText=a##buttonText,
       )
     );
};

let findOpt = (path, quiz) => {
  let filteredQuizArray = quiz |> Js.Array.filter(q => q.path == path);
  filteredQuizArray |> ArrayUtils.isEmpty
    ? None : filteredQuizArray |> ArrayUtils.getOpt(0);
};
