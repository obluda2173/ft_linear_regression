CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror

SRC_DIR := src/cpp
SRC_PY := src/python
DATA_DIR := data
BUILD_DIR := bin

TRAIN_SRC := $(SRC_DIR)/train.cpp
PREDICT_SRC := $(SRC_DIR)/predict.cpp
GRAPH_SRC := $(SRC_PY)/graph.py

TRAIN_BIN := $(BUILD_DIR)/train
PREDICT_BIN := $(BUILD_DIR)/predict

RED   := \033[1;31m
GREEN := \033[1;32m
BLUE  := \033[1;34m
RESET := \033[0m

all: $(TRAIN_BIN) $(PREDICT_BIN)
	@echo "$(GREEN)✔ Build complete$(RESET)"

re: clean all

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TRAIN_BIN): $(TRAIN_SRC) | $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "$(BLUE)✔ train built$(RESET)"

$(PREDICT_BIN): $(PREDICT_SRC) | $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "$(BLUE)✔ predict built$(RESET)"

run: run-train run-predict

run-train: $(TRAIN_BIN)
	@cd $(SRC_DIR) && ../../$(TRAIN_BIN)

run-predict: $(PREDICT_BIN)
	@cd $(SRC_DIR) && ../../$(PREDICT_BIN)

graph: $(GRAPH_SRC)
	@cd $(SRC_PY) && python3 graph.py
	@echo "$(BLUE)✔ Graph generated$(RESET)"

clean:
	@rm -fr $(BUILD_DIR) $(DATA_DIR)/model.json
	@echo "$(RED)✔ Cleaned$(RESET)"

.PHONY: all clean run-train run-predict
