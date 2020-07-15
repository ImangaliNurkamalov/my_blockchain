# my_blockchain

## Command
`my_blockchain`

## Description
Blockchain is a command to create and manage a blockchain. When the program starts it loads a backup blockchain if there is any; then, a prompt appears.
The prompt allows to execute blockchain commands. When the commands are successful it will process as normally, otherwise, i.e. if error appears, it displays "error:INFO" as shown in **Error Messages** field.

For blockchain key commands see below:
- **add node _node_id_** add a _node_id_ "Node Identifier" to the blockchain node
- **rm node _node_id_** removes node from the blockchain with _node_id_ "Node Identifier". If _node_id_ is '*', then all nodes are removed
- **add block _block_id_ _node_id_** add a _block_id_ "Block Identifier" to blockchain node with _node_id_ "Node Identifier". If _node_id_ is '*', then _block_id_ is added to all blockchain nodes
- **rm block _lock_id_** removes _block_id_ "Block Identifier" from all nodes where these blocks are present
- **ls** list all nodes by their identifiers. If an option **-l** is attached, then additionally block identifiers associated to the node are listed
- **sync** synchronizes all of the nodes with each other. Upon issuing this command, all of the nodes are composed of the same blocks
- **quit** save and leave the blockchain

### The blockchain prompt displays (see example below):

a **[** charachter\
a first letter that indicates the state of synchronization of the chain:\
"**s**" if the blockchain is synchronized\
"**-**" if the blockchain is not synchronized.\
**n** number of nodes in the chain.\
the "**]>** " string (with a space)

## Error messages
1. "No more resources available on the computer"
2. "This node already exists"
3. "This block already exists"
4. "Node does not exist"
5. "Block does not exist"
6. "Command not found"

## Run
```
make
./my_blockchain [first arg optional backup file second arg optional save clockchin file]

For example:
./my_blockchain // No backup blockchain is read, and blockchain will not be saved
./my_blockchain backup.txt // Blockchain will first read from backup and will not save
./my_blockchain backup.txt save.txt // Blockchain will first read from backup and finally save the blockchain to save.txt (If backup.txt does not exist, the blockchain will still work and save the blockchain to save.txt)
```

## Technical Information
```
$>my_blockhain
[-0]> add node 12
[-1]> add block 21 *
[-1]> add node 13
[-2]> ls -l
12: 21
13:
[-2]> sync
[s2]> ls -l
12: 21
13: 21
[s2]> quit
```
