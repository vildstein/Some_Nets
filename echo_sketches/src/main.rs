use std::net::UdpSocket;
use std::io::Error;
use std::process;
use std::env;
//use std::sync::mpsc::RecvError;

mod parse_cli_args_fn;
use parse_cli_args_fn::parse_cli_args;

fn main() {
    let argv : Vec<String> = env::args().collect();

    let addr : String = parse_cli_args(argv);

    let udp_socket = socket_func_wrap();

    let connect_res = connect_func_wrap(&udp_socket, addr);

    if connect_res.is_err() {
        println!("connection func failed");
        process::exit(1);
    } else {
        println!("binded with UDP");
    }



    let send_result = send_dgram(&udp_socket);

    if send_result.is_ok() {
        let bytes_sended = send_result.unwrap();
        println!("sended {} bytes", bytes_sended);

    } else {
        println!("send func mistake");
    }

    //if send_result.is_ok() {
    try_recv(&udp_socket);
   // }
}

fn socket_func_wrap() -> UdpSocket {

    let initial_zero_addr = "0.0.0.0:0";
    let udp_socket_res = UdpSocket::bind(initial_zero_addr);

    if udp_socket_res.is_err() {
        println!("SOCKET func creation mistake");
        println!("UNABLE create udp socket");
        process::exit(1);
    }

    udp_socket_res.unwrap()
}

fn connect_func_wrap(udp_sock : &UdpSocket, addr_port : String) -> Result<(), Error> {
    let addr_port_str = addr_port.as_str();
    let connect_result =  udp_sock.connect(&addr_port_str);
    connect_result
}

fn send_dgram(udp_sock : &UdpSocket) -> Result<usize, Error> {

    let d_gram : [u8; 7] = [0, 1, 2, 3, 4, 5, 6];
    let res = udp_sock.send(&d_gram);

    res
}

fn try_recv(udp_sock : &UdpSocket)  {

    let mut buf: [u8; 10] = [0; 10];

    let recv_res = udp_sock.recv(&mut buf);

    if recv_res.is_ok() {
        let bytes_recieved = recv_res.unwrap();
        println!("received {bytes_recieved} bytes {:?}", &buf[..bytes_recieved]);
    } else {
        println!("recv func mistake");
    }
}
