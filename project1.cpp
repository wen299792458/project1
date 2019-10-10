#include <iostream>
#include <iostream>
#include <iostream>
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
    void show_matrix();
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
    //istream input("1.in", ios::in);
    //ostream output("1.out", ios::out);
    string type;
    int rows, cols, col;
    cin >> rows;
    cin >> cols;
    Matrix M(rows, cols);
    while(true){
        cin >> type;
        if(type == "End") break;
        cin >> col;
        M.one_block(type, col-1);
        if(M.is_end()) break;
        M.show_matrix();
    }
    cout << endl << endl << "Now is end" << endl;
    M.show_matrix();
}

bool Matrix::is_end(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < cols; j++){
            if (matrix[i][j] == true){
                cout<<"now is end";
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
    else if( B->type == "T2" && (matrix[B->row][B->col] == true || matrix[B->row+1][B->col] == true)){
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
    else if( B->type == "S2" && (matrix[B->row][B->col] == true || matrix[B->row+1][B->col] == true)){
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