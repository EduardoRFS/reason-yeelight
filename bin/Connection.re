type t = Unix.file_descr;

let connect = (host, port) => {
  let addr =
    Unix.ADDR_INET(Unix.inet_addr_of_string("192.168.15.20"), 55443);
  let socket = Unix.socket(Unix.PF_INET, Unix.SOCK_STREAM, 0);
  Unix.connect(socket, addr);
  socket;
};

let send_command = (t, command) =>
  Command.serialize(command)
  |> Base.Result.map(~f=json => {
       let message = Yojson.to_string(json) ++ "\r\n";
       Unix.write_substring(t, message, 0, String.length(message));

       let output = Bytes.make(255, '\000');
       Unix.read(t, output, 0, 255);

       print_endline(output |> Bytes.to_string);
     });

let close = t => Unix.close(t);