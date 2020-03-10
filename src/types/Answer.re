type t = {
  title: string,
  description: array(string),
  imageUrl: option(string),
  youtubeUrl: option(string),
  correctAnswer: bool,
};

let make =
    (~title, ~description, ~imageUrl=None, ~youtubeUrl=None, ~correctAnswer) => {
  {title, description, imageUrl, youtubeUrl, correctAnswer};
};

let title = t => t.title;
let description = t => t.description;
let youtubeUrl = t => t.youtubeUrl;
let imageUrl = t => t.imageUrl;
let correctAnswer = t => t.correctAnswer;

let makeArray = answers => {
  answers
  |> Array.map(a => {
       Js.log(a##description);
       make(
         ~title=a##title,
         ~description=a##description |> Array.map(d => d),
         ~imageUrl=a##imageUrl,
         ~youtubeUrl=a##youtubeUrl |> Js.Nullable.toOption,
         ~correctAnswer=a##correctAnswer,
       );
     });
};
