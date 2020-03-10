let str = React.string;
let logo: string = [%raw "require('../assets/coronasafe.png')"];

let json = [%bs.raw {|require("./data.json")|}];
let data = json |> Data.decode;

let showHome = () => {
  <div className="rounded overflow-hidden shadow-lg p-4">
    <div className="px-6 py-4">
      <div className="font-bold text-xl mb-2"> {"Are you safe?" |> str} </div>
      <button
        onClick={_ => ReasonReactRouter.push("/quiz")}
        className="text-gray-700 text-base btn border hover:bg-indigo-900 hover:text-white">
        {"Let's checkout" |> str}
      </button>
    </div>
  </div>;
};

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  <div className="my-10 mx-2 max-w-xl mx-auto">
    <a href="./">
      <img
        className="object-contain w-full"
        src=logo
        alt="Sunset in the mountains"
      />
    </a>
    <div className="max-w-xl mt-2">
      {switch (url.path) {
       | ["quiz"] => <QuizComponent questions={data |> Data.questions} />
       | _ => showHome()
       }}
    </div>
  </div>;
};
