CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror

SRC_DIR := src/cpp
DATA_DIR := data
BUILD_DIR := bin

TRAIN_SRC := $(SRC_DIR)/train.cpp
PREDICT_SRC := $(SRC_DIR)/predict.cpp

TRAIN_BIN := $(BUILD_DIR)/train
PREDICT_BIN := $(BUILD_DIR)/predict

all: $(TRAIN_BIN) $(PREDICT_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TRAIN_BIN): $(TRAIN_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(PREDICT_BIN): $(PREDICT_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

run-train: $(TRAIN_BIN)
	cd $(SRC_DIR) && ../../$(TRAIN_BIN)

run-predict: $(PREDICT_BIN)
	cd $(SRC_DIR) && ../../$(PREDICT_BIN)

clean:
	rm -fr $(BUILD_DIR)
	rm -fr $(DATA_DIR)/model.json

.PHONY: all clean run-train run-predict
