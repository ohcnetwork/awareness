let str = React.string;

type page =
  | Quiz
  | Complete;

type state = {
  page,
  selectedAnser: option(Answer.t),
  currentQuestionIndex: int,
};

let updateAnswer = (setState, answer, _event) => {
  setState(state => {...state, selectedAnser: Some(answer)});
};

let showSelectedAnswer = state => {
  switch (state.selectedAnser) {
  | Some(answer) =>
    <div className="px-6 py-4">
      <div className="font-bold text-xl mb-2">
        {answer |> Answer.title |> str}
      </div>
      <div>
        {answer
         |> Answer.description
         |> Array.mapi((index, d) =>
              <div key={index |> string_of_int}> {d |> str} </div>
            )
         |> React.array}
      </div>
      {switch (answer |> Answer.youtubeUrl) {
       | Some(src) => <iframe className="w-full" height="auto" src />
       | None => React.null
       }}
    </div>
  | None => React.null
  };
};

let showQuestion = (question, setState, state) => {
  <div className="px-6 py-4">
    <div className="font-bold text-xl mb-2">
      {question |> Question.title |> str}
    </div>
    <div>
      {question
       |> Question.answers
       |> Array.map(answer => {
            <div key={answer |> Answer.title}>
              <button
                className="text-gray-700 text-base btn border hover:bg-indigo-900 hover:text-white btn-large mt-2 w-full"
                onClick={updateAnswer(setState, answer)}>
                {answer |> Answer.title |> str}
              </button>
            </div>
          })
       |> React.array}
    </div>
    <div> {showSelectedAnswer(state)} </div>
  </div>;
};

let nextQuestion = (setState, _event) => {
  setState(state =>
    {
      ...state,
      currentQuestionIndex: state.currentQuestionIndex + 1,
      selectedAnser: None,
    }
  );
};

let showSucess = () => {
  <div>
    <div> {"You are safe Now!" |> str} </div>
    <button
      onClick={_ => ReasonReactRouter.push("/")}
      className="text-gray-700 text-base btn border hover:bg-indigo-900 hover:text-white">
      {"Home" |> str}
    </button>
  </div>;
};

let showQuiz = (questions, currentQuestion, setState, state) => {
  let isLastQuestion =
    !(state.currentQuestionIndex < (questions |> Array.length) - 1);

  <div>
    <div>
      {switch (currentQuestion) {
       | Some(question) => showQuestion(question, setState, state)
       | None => React.null
       }}
    </div>
    <div>
      {switch (state.selectedAnser) {
       | Some(_) =>
         isLastQuestion
           ? <button
               onClick={_ => setState(state => {...state, page: Complete})}
               className="text-gray-700 text-base btn border hover:bg-indigo-900 hover:text-white">
               {"Complete" |> str}
             </button>
           : <button
               onClick={nextQuestion(setState)}
               className="text-gray-700 text-base btn border hover:bg-indigo-900 hover:text-white">
               {"Next Question" |> str}
             </button>
       | None => React.null
       }}
    </div>
  </div>;
};

[@react.component]
let make = (~questions) => {
  let (state, setState) =
    React.useState(() =>
      {currentQuestionIndex: 0, selectedAnser: None, page: Quiz}
    );
  let currentQuestion =
    questions |> ArrayUtils.getOpt(state.currentQuestionIndex);

  <div className="rounded overflow-hidden shadow-lg p-4">
    {switch (state.page) {
     | Quiz => showQuiz(questions, currentQuestion, setState, state)
     | Complete => showSucess()
     }}
  </div>;
};
