CLIENT = client/cpp
SERVER = server

.PHONY: project_code

project_code:
	$(MAKE) -C $(CLIENT)
	$(MAKE) -C $(SERVER)

clean:
	$(MAKE) -C $(CLIENT) clean
	$(MAKE) -C $(SERVER) clean