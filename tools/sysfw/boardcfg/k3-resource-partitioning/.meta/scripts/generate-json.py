import json
import sys
socJson = sys.argv[1] # Path to SoC JSON
with open(socJson, "r") as file:
    soc = json.load(file)
    
with open("./ip.json", "w") as file:
    json.dump(soc['ip_instances'], file)
    
with open("./qos.json", "w") as file:
    json.dump(soc['qos'], file)
    
with open("./security.json", "w") as file:
    json.dump(soc['security'], file)
    
