# sshFilter
This is a packet filter firewall module that filters for and blocks any outgoing packet to port number 22 (SSH)

# Packet Filter Firewall (sshFilter)

This is a packet filter firewall implementation that is designed to block all outgoing packets on port 22 (SSH). This tool can be useful for controlling network access on a system by filtering outgoing traffic based on port numbers.

## Features

- Blocks all outgoing packets on port 22 (SSH).
- Simple and lightweight implementation.
- Written in C.

## Prerequisites

Before using this firewall, ensure you have the following dependencies installed:

- `iptables` 

## Installation

### Clone the repository

```bash
git clone https://github.com/hotwrist/sshFilter.git
cd sshFilter
```

## How it works

The firewall intercepts outgoing network packets and checks whether they are destined for port 22. If a packet matches, it is blocked; otherwise, the packet is allowed to pass through.

## Configuration

You can modify the source code to change the port number or extend functionality to filter other ports, if desired.

For example, if you want to block another port, just replace `22` with the port number you want to filter in the code.

## Troubleshooting

If you encounter any issues with the firewall, check the following:

- Ensure you have the necessary permissions to run the firewall (you may need root privileges).
- Verify that your network interface is configured correctly.
- Review any error messages printed to the console for hints on what went wrong.

## Contributing

Feel free to submit issues or pull requests if you find any bugs or would like to add features. Contributions are welcome!

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
