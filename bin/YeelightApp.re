open Command;

let host = Sys.argv[1];
let color = {
  let r = Sys.argv[2] |> int_of_string;
  let g = Sys.argv[3] |> int_of_string;
  let b = Sys.argv[4] |> int_of_string;
  let a = Sys.argv[5] |> float_of_string;
  Color.Rgba.{r, g, b, a};
};
let connection = Connection.connect(host, 55443);
Connection.send_command(connection, SET_SCENE(COLOR(color)));
Connection.close(connection);