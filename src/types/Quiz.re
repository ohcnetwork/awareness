type t = {
  title: string,
  path: string,
  questions: array(Question.t),
  buttonText: string,
  readMore: string,
  successMessage: string,
  description: string,
};

let make =
    (
      ~title,
      ~path,
      ~questions,
      ~buttonText,
      ~readMore,
      ~successMessage,
      ~description,
    ) => {
  {title, path, questions, buttonText, successMessage, readMore, description};
};

let title = t => t.title;
let path = t => t.path;
let questions = t => t.questions;
let buttonText = t => t.buttonText;
let readMore = t => t.readMore;
let successMessage = t => t.successMessage;
let description = t => t.description;

let makeArray = json => {
  json
  |> Array.map(a =>
       make(
         ~title=a##title,
         ~path=a##path,
         ~questions=a##questions |> Question.makeArray,
         ~buttonText=a##buttonText,
         ~readMore=a##readMore,
         ~successMessage=a##successMessage,
         ~description=a##description,
       )
     );
};

let findOpt = (path, quiz) => {
  let filteredQuizArray = quiz |> Js.Array.filter(q => q.path == path);
  filteredQuizArray |> ArrayUtils.isEmpty
    ? None : filteredQuizArray |> ArrayUtils.getOpt(0);
};
