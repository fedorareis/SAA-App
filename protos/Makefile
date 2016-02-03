DEST_DIR=dist

all:
	mkdir -p $(DEST_DIR)/cpp $(DEST_DIR)/java $(DEST_DIR)/python 
	protoc --cpp_out=$(DEST_DIR)/cpp --java_out=$(DEST_DIR)/java --python_out=$(DEST_DIR)/python adsb.proto ownship.proto radar.proto tcas.proto cdti.proto

clean:
	rm -r $(DEST_DIR)
