#pragma once

const std::string FILE_PATH = "graph.txt";
const std::string GRAPH_LOADED = "Tree loaded from file " + FILE_PATH;
const std::string ERROR_FILE_IS_NOT_OPEN = "File is not open!";
const std::string ERROR_WRONG_FORMAT = "Wrong file format!";
const std::string ERROR_WRONG_INPUT_FORMAT = "Wrong input format!";
const std::string ERROR_FROM_TO_EQUAL = "FROM and TO tops must be not equal!";
const std::string ERROR_TOP_NOT_EXISTS = "Input top is not exists!";

const std::string ERROR_DOUBLE_ARC_DEFINITION = "Double arc definition!";
const std::string TOPS_EMPTY = "Tops is empty.";
const std::string ARCS_EMPTY = "Arcs is empty.";
const std::string ARCS_DELETED = "Arcs deleted.";
const std::string TOPS_DELETED = "Tops deleted.";
const std::string DATA_LOADED = "Data loaded from file " + FILE_PATH;
const std::string INPUT_TOPS_FOR_FIND_PATH = "Enter two tops (FROM and TO) through space: ";
const std::string OPERATION_CANCELED = "Operation canceled!";
const std::string FORMAT_FILE_EQ = "^([a-zA-Z]{1,})\\s-\\s([a-zA-Z]{1,})\\s([0-9]{1,})$";
const std::string FORMAT_FILE_TO = "^([a-zA-Z]{1,})\\s<-\\s([a-zA-Z]{1,})\\s([0-9]{1,})$";
const std::string FORMAT_FILE_FR = "^([a-zA-Z]{1,})\\s->\\s([a-zA-Z]{1,})\\s([0-9]{1,})$";
const std::string FORMAT_INPUT_2_TOPS = "^([a-zA-Z]{1,})\\s([a-zA-Z]{1,})$";
const std::string MENU_TEXT = R"("====================== Task 3.18 ======================="
"========================================================"
"= Enter each command finish pressing button <Enter>.   ="
"=                                                      ="
"= Commands:                                            ="
"= `a` - load graph from file                           ="
"= `s` - print tops and arcs                            ="
"= `d` - find shortest path between tops                ="
"= `f` - delete tops and arcs                           ="
"=                                                      ="
"= `q` - close                                          ="
"========================================================")";
