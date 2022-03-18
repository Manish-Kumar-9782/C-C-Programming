// In this section we will remove the problam occured in the CalculatorX0 program.

/*
    Problams In CalCulatorX0 program:

        * it skips the tokens.
        * it does not use the tokens.
        * return tokens only which are placed at odd positions.
    
    In this section we will try to remove the skipping of token problem using the token stream.

    Token Stream: Token stream is a class/mechanism to control the input token as to get the next token and also put back the 
        current token back to the stram, The purpose of  using this mechanism is don't skip a token when it is not used. store 
        it in the stream and use it later in aonther function. 
*/

// Now first of all we need to include the iostream files.

#include<iostream>
using namespace std;

// Now we will make a Token class

class Token{
    public:
        char kind;
        double value;

        Token(char ch): kind(ch) {}
        // Initializing the Token only with char

        Token(char ch, double val): kind(ch), value(val) {}
        // Initializing the the Token with both kind and value.
};

// Now we will make a TokenStream Class
/*
    Token stream must have to function
    get: to get the value stored in the buffer or form the input stream
    putback: to store the unused token in the token stream which will be used later in any other function.
*/
Token GetToken(); // this function will be used to get the token form the input stream.

class TokenStream{

    private:
        bool full; // a bool variable which will show that a TokenStream buffer is full or empty.
        Token buffer; // In this buffer we will hold the unused token.

    public: // Now we will declare all the function which will be used by the user.
        TokenStream(): full(false), buffer(0) {}

        // Now we will define the get function.
        Token get(){
            // this function will return the token if there is any token available in the buffer.
            if(full) {
                full = false; // setting buffer setting as false means our buffer is ready for next token
                return buffer;
            }
            // if we dont have any token then we will get the token from the input
            else 
                return GetToken();
        }

        // Now we will make a member function which will help us to hold or store the unused token 
        void putback(Token t){
            // since this function does not return anything it has void return type.
            // Now first of all we need to check that buffer is empty or not
            if(!full)  
            {
                buffer = t; // copying the t (token) in the buffer
                full = true; // setting the full as true it means that buffer is full.
            }
            else
                throw("buffer is full can't hold the current token");
        }

};

// Now we will declare all the required other function for calculator like 
// Expression, Term, Primary.
TokenStream ts;

double Expression();
double Term();
double Primary();

// Now we will make a global variable for the Token stream
int main(){

    // Now we will littil change our code from X0 version.

    double val = 0;
    
    while(cin){

        Token t = ts.get();  // getting the very first token it should be a numeric value.

        if(t.kind == 'q') break;
        if(t.kind == ';')
            cout<<"="<<val<<endl;
        else ts.putback(t);

        val = Expression();
        
        
    }

    return 0;
}

Token GetToken(){
    char ch;
    cin>>ch;

    switch(ch){

        case 'q': // for quit
        case ';': // for print
        case '(': case ')': case '+': case '-': case '*': case '/':
            return Token(ch);        // let each character represent itself
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin>> val;              // read a floating-point number
            return Token('N', val);   // let 'N' represent "a number"
        }
        default:
            throw("Bad token");
    }
}


/*==============================================================================================================*/
// 1. Defining the expression function opearion.
double Expression(){
    /*
        This function will return the double dtype value and it will compute the + and - computation

        Expression:
            Term
            Expression "+" Term;
            Expression "-" Term;
    */

   // Now first of all we will get the term as the left operand of the + or -;

   double left = Term(); // this will return the a double value.
   
   // Now we will get the next token to get the Opearator.

   Token t = ts.get();
   //cout<<"Got "<<t.kind<<" Operator"<<endl;
   while(true){
       // while we dont return the left we will run the loop 
       //cout<<"In expression while loop"<<endl;
       switch (t.kind)
        {
            case '+':
                //cout<<"adding values"<<endl;
                left += Term();  // if we get the + operator then we will add next term with this.
                t = ts.get(); // we will get next token after getting calculated the above value 
                break;

            case '-':
                //cout<<"Subtracting values"<<endl;
                left -= Term();
                t = ts.get(); // we will get next token after getting calculated the above value 
                break;
            default:
                ts.putback(t);
                return left; // if ther is no + or - then we will return the result.
        }
    }
}

// 2. defining the Term operation.
double Term(){

    /*
        This function will be used to compute the *, / operation.
        Term:
            Primary
            Term * Primary;
            Term / Primary;

        The defination of this function is almost similar to the expression fucntion. 
    */

    // first of all we will get the double dtype value from the Primary function.
    double left = Primary();

    // Now we will get the next token
    Token t = ts.get();
   // cout<<"Got "<<t.kind<<" Operator"<<endl;
    // Now we will use the switch cases while don't return the result form this funciton.
    while (true) // infinte loop
    {   
        // cout<<"In term while loop"<<endl;     
        switch (t.kind)
        {
            case '*':
                left *= Primary();
                t = ts.get();
                break;
            
            case '/':
                // here to avoid the devision by zero we need to use the exception.
                { // if we are initializing a variable in a case then we need to put them into a block.
                    double result = Primary();
                    if(result == 0) throw("Devision By Zero");
                    left /= result;
                    t = ts.get();
                    break;
                }

            default:
                ts.putback(t);
                return left;
        }    /* code */
    }
    
}

// 3. A Primary function which will handle the Paranthesis expressions.
double Primary(){
    // This function will return the double value after calculation.
    /*
        Primary:
            Number
            "(" expression ")"
        
        Now this will handle two kind of operations, either it will return the Number or it will compute the expression
        binded by paranthesis.

    */
   Token t = ts.get();  // Now after getting the token we need to check it's kind.
//    cout<<"Got "<<t.kind<<" Operator"<<endl;
//    cout<<"In Primary after getting Token"<<endl;
   switch (t.kind)
   {
    case '(': // handle the "(" expression ")";
        {
            double d = Expression();
            // after getting the result form the expression we expect a token of '(' 
            t = ts.get();

            if(t.kind != ')' ) throw("expected ')' token ");
            return d; // return the result if we get the full '(expression)'
        }
   
    case 'N':
        //ts.putback();
        return t.value;  // if we get a number then we will return the number.

    default:
        throw("Primary expected");
       
   }
}

/*
Conclusion: This CalCulator application now can calculate the +, -, *, and / operation and it can handle also '(expression)'

    Note: This CalCulator is not perfect and can't handle various type of bad input 
*/