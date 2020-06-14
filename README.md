# my_blockchain

## Hello reveiwer
Welcome to blockchain!

## Run
```
make
./my_blockchain [first arg optional backup file second arg optional save clockchin file]

For example:
./my_blockchain // No backup blockchain is read, and blockchain will not be saved
./my_blockchain backup.txt // Blockchain will first read from backup and will not save
./my_blockchain backup.txt save.txt // Blockchain will first read from backup and finally save the blockchain to save.txt (If backup.txt does not exist, the blockchain will still work and save the blockchain to save.txt)
```