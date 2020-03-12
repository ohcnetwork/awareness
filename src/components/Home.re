let str = React.string;
let logo: string = [%raw "require('../assets/coronaSafeLogo.png')"];

let json = [%bs.raw {|require("./data.json")|}];
let data = json |> Data.makeData;

let showHome = data => {
  <div className="rounded overflow-hidden">
    {data
     |> Data.quiz
     |> Array.map(q =>
          <div className="p-4 rounded border mt-4">
            <div className="font-bold text-xl mb-2">
              {q |> Quiz.title |> str}
            </div>
            <div className="text-sm mb-2">
              {q |> Quiz.description |> str}
            </div>
            <button
              onClick={_ => ReasonReactRouter.push(q |> Quiz.path)}
              className="text-gray-700 text-base btn border hover:bg-indigo-900 hover:text-white">
              {q |> Quiz.buttonText |> str}
            </button>
          </div>
        )
     |> React.array}
  </div>;
};

let showQuiz = (path, data) => {
  switch (data |> Data.quiz |> Quiz.findOpt(path)) {
  | Some(quiz) => <QuizComponent quiz />
  | None => showHome(data)
  };
};

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  <div className="my-10 mx-2 max-w-xl mx-auto">
    <a href="./">
      <img
        className="object-contain w-full p-4"
        src=logo
        alt="Sunset in the mountains"
      />
    </a>
    <div className="max-w-xl m-2">
      {switch (url.path) {
       | [path] => showQuiz(path, data)
       | _ => showHome(data)
       }}
    </div>
  </div>;
};
