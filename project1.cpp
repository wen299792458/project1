#include <iostream>
#include <fstream>
using namespace std;

class Block;

class Matrix{
    private:
    bool **matrix;
    int rows, cols;
    Block *B;
    public:
    Matrix(int rows, int cols):rows(rows), cols(cols){
        matrix = new bool*[rows+5];  //reserve place for input block
        for(int i = 0; i < rows + 5; i++){
            matrix[i] = new bool[cols];  
        }
        for(int i = 0; i < rows + 5; i++){
            for(int j = 0; j < cols; j++){
                if(i == rows + 4) matrix[i][j] = true;
                else matrix[i][j] = false;
            }
        }

    }
    ~Matrix(){
        for(int i = 0; i < cols; i++)
            delete [] matrix[i];
        delete [] matrix;
    }
    bool is_end();
    void one_block(string type, int col);
    void show_matrix(ofstream& output);
    void cancel();
    void write(bool write_or_wipe);
    bool check_stop();
};

struct Block{
    int row, col;
    string type;
    Block(string in_type, int in_col){
        row = 3;     //reserved place for inpute block
        col = in_col;
        type = in_type;
    }
};

int main(){
    ifstream input("Tetris.data", ios::in);
    ofstream output("Tetris.output", ios::out);
    if(input.eof()) cout << "input error" << endl;
    else if(output.eof()) cout << "output error" << endl;
    else cout << "success" << endl;

    string type;
    int rows, cols, col;
    input >> rows;
    input >> cols;
    Matrix M(rows, cols);
    while(true){
        input >> type;
        if(type == "End") break;
        input >> col;
        M.one_block(type, col-1);
        M.cancel();
        if(M.is_end()) break;
      //  M.show_matrix();
    }
    //cout << endl << endl << "Now is end" << endl;
    M.show_matrix(output);
    input.close();
    output.close();
}

bool Matrix::is_end(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < cols; j++){
            if (matrix[i][j] == true){
                return true;
            }
        }
    }
    return false;
}

void Matrix::one_block(string type, int col){
    B = new Block(type,col);
    while(!(check_stop())){
        write(0);
        B->row++;      //fall
        write(1);
    }
    delete B;
}

void Matrix::show_matrix(ofstream& output){
    for(int i = 4; i < rows + 4; i++){
        for(int j = 0; j < cols; j++){
            output << matrix[i][j] ;
        }
        output << endl;
    }
}

void Matrix::cancel(){
    bool cancel, final_check;
    int line;
    do{
        final_check = true;
        for(int i = rows + 3; i > 3; i--){
            cancel = true;
            for(int j = 0; j < cols; j++){
                if(matrix[i][j] == false){
                    cancel = false;
                }
            }
            if(cancel == true){
                final_check = false;
                for(int i2 = i; i2 > 0; i2--){
                    for(int j2 = 0; j2 < cols; j2++){
                        matrix[i2][j2] = matrix[i2-1][j2];
                    }
                }
            }
        }
    }while(!final_check);
}


void Matrix::write(bool write_or_wipe){
    bool output;
    if(write_or_wipe){
        output = true;
    }
    else output = false;
    if(B->type == "T1"){
        matrix[B->row][B->col+1] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-1][B->col+2] = output;
    }
    if(B->type == "T2"){
        matrix[B->row][B->col+1] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-2][B->col+1] = output;
    }
    if(B->type == "T3"){
        matrix[B->row][B->col] = output;
        matrix[B->row][B->col+1] = output;
        matrix[B->row][B->col+2] = output;
        matrix[B->row-1][B->col+1] = output;
    }
    if(B->type == "T4"){
        matrix[B->row][B->col] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-2][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
    }
    if(B->type == "L1"){
        matrix[B->row][B->col] = output;
        matrix[B->row][B->col+1] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-2][B->col] = output;
    }
    if(B->type == "L2"){
        matrix[B->row][B->col] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-1][B->col+2] = output;
    }
    if(B->type == "L3"){
        matrix[B->row][B->col+1] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-2][B->col+1] = output;
        matrix[B->row-2][B->col] = output;
    }
    if(B->type == "L4"){
        matrix[B->row][B->col] = output;
        matrix[B->row][B->col+1] = output;
        matrix[B->row][B->col+2] = output;
        matrix[B->row-1][B->col+2] = output;
    }
    if(B->type == "J1"){
        matrix[B->row][B->col] = output;
        matrix[B->row][B->col+1] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-2][B->col+1] = output;
    }
    if(B->type == "J2"){
        matrix[B->row][B->col] = output;
        matrix[B->row][B->col+1] = output;
        matrix[B->row][B->col+2] = output;
        matrix[B->row-1][B->col] = output;
    }
    if(B->type == "J3"){
        matrix[B->row][B->col] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-2][B->col] = output;
        matrix[B->row-2][B->col+1] = output;
    }
    if(B->type == "J4"){
        matrix[B->row][B->col+2] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-1][B->col+2] = output;
    }
    if(B->type == "S1"){
        matrix[B->row][B->col] = output;
        matrix[B->row][B->col+1] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-1][B->col+2] = output;
    }
    if(B->type == "S2"){
        matrix[B->row][B->col+1] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-2][B->col] = output;
    }
    if(B->type == "Z1"){
        matrix[B->row][B->col+1] = output;
        matrix[B->row][B->col+2] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
    }
    if(B->type == "Z2"){
        matrix[B->row][B->col] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
        matrix[B->row-2][B->col+1] = output;
    }
    if(B->type == "I1"){
        matrix[B->row][B->col] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-2][B->col] = output;
        matrix[B->row-3][B->col] = output;
    }
    if(B->type == "I2"){
        matrix[B->row][B->col] = output;
        matrix[B->row][B->col+1] = output;
        matrix[B->row][B->col+2] = output;
        matrix[B->row][B->col+3] = output;
    }
    if(B->type == "O"){
        matrix[B->row][B->col] = output;
        matrix[B->row][B->col+1] = output;
        matrix[B->row-1][B->col] = output;
        matrix[B->row-1][B->col+1] = output;
    }
}

bool Matrix::check_stop(){
    if( B->type == "T1" && (matrix[B->row][B->col] == true || matrix[B->row+1][B->col] == true || matrix[B->row][B->col+2] == true)){
        return true;
    }
    else if( B->type == "T2" && (matrix[B->row][B->col] == true || matrix[B->row+1][B->col+1] == true)){
        return true;
    }
    else if( B->type == "T3" && (matrix[B->row+1][B->col] == true || matrix[B->row+1][B->col+1] == true || matrix[B->row+1][B->col+2] == true)){
        return true;
    }
    else if( B->type == "T4" && (matrix[B->row+1][B->col] == true || matrix[B->row][B->col+1] == true)){
        return true;
    }
    else if( B->type == "L1" && (matrix[B->row+1][B->col] == true || matrix[B->row+1][B->col+1] == true)){
        return true;
    }
    else if( B->type == "L2" && (matrix[B->row+1][B->col] == true || matrix[B->row][B->col+1] == true || matrix[B->row][B->col+2] == true)){
        return true;
    }
    else if( B->type == "L3" && (matrix[B->row-1][B->col] == true || matrix[B->row+1][B->col+1] == true)){
        return true;
    }
    else if( B->type == "L4" && (matrix[B->row+1][B->col] == true || matrix[B->row+1][B->col+1] == true || matrix[B->row+1][B->col+2] == true)){
        return true;
    }
    else if( B->type == "J1" && (matrix[B->row+1][B->col] == true || matrix[B->row+1][B->col+1] == true)){
        return true;
    }
    else if( B->type == "J2" && (matrix[B->row+1][B->col] == true || matrix[B->row+1][B->col+1] == true || matrix[B->row+1][B->col+2] == true)){
        return true;
    }
    else if( B->type == "J3" && (matrix[B->row+1][B->col] == true || matrix[B->row-1][B->col+1] == true)){
        return true;
    }
    else if( B->type == "J4" && (matrix[B->row][B->col] == true || matrix[B->row][B->col+1] == true || matrix[B->row+1][B->col+2] == true)){
        return true;
    }
    else if( B->type == "S1" && (matrix[B->row+1][B->col] == true || matrix[B->row+1][B->col+1] == true || matrix[B->row][B->col+2] == true)){
        return true;
    }
    else if( B->type == "S2" && (matrix[B->row][B->col] == true || matrix[B->row+1][B->col+1] == true)){
        return true;
    }
    else if( B->type == "Z1" && (matrix[B->row][B->col] == true || matrix[B->row+1][B->col+1] == true || matrix[B->row+1][B->col+2] == true)){
        return true;
    }
    else if( B->type == "Z2" && (matrix[B->row+1][B->col] == true || matrix[B->row][B->col+1] == true)){
        return true;
    }
    else if( B->type == "I1" && (matrix[B->row+1][B->col] == true)){
        return true;
    }
    else if( (B->type == "I2") && (matrix[B->row+1][B->col] == true || matrix[B->row+1][B->col+1] == true || matrix[B->row+1][B->col+2] == true || matrix[B->row+1][B->col+3] == true)){
        return true;
    }
    else if( B->type == "O" && (matrix[B->row+1][B->col] == true || matrix[B->row+1][B->col+1] == true)){
        return true;
    }
    else return false;
}