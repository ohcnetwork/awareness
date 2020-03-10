let str = React.string;
let logo: string = [%raw "require('./assets/coronasafe.png')"];

[@react.component]
let make = () =>
  <div className="h-screen flex justify-center items-center">
    <div className="max-w-sm rounded overflow-hidden shadow-lg p-4">
      <img className="w-full" src=logo alt="Sunset in the mountains" />
      <div className="px-6 py-4">
        <div className="font-bold text-xl mb-2">
          {"Are you safe?" |> str}
        </div>
        <p className="text-gray-700 text-base"> {"Let's checkout" |> str} </p>
      </div>
    </div>
  </div>;
