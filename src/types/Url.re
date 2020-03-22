module Quiz = {
  let parse = questionFragment =>
    try(
      Some(
        {
          let v = int_of_string(questionFragment);
          if (v < 0) {
            0; /* Quick and dirty validation */
          } else {
            v - 1;
          };
        },
      )
    ) {
    | _ => None
    };
};
