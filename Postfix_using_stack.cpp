#include <iostream>
 #include<cmath> 
 using namespace std;
 class Stack { 
    private:
     int arr[100]; 
     int top; 
     public:
      Stack() { 
        top =-1;
     }
      void push(int val) {
         arr[++top] = val;
         } 
         int pop() { 
            int p = arr[top--];
             return p;
     }
    };
    int evaluate(char x,int op1,int op2) 
    { 
     if(x=='+') return(op1+op2); 
     if(x=='-') return(op1-op2); 
      if(x=='*') return(op1*op2); 
      if(x=='/') return(op1/op2); 
     if(x=='%') return(op1%op2); 
    if(x=='$') return(pow(op1,op2)); 
} 
                int main(void)
                 {
                     Stack s; 
                     char x;
                      int op1,op2,val;
                       cout<<"\n Enter postfix Expression :";
                        while((x= getchar()) != '\n')
                         { 
                            if(isdigit(x)) 
                            {
                                s.push(x-48);
                            }
                            else
                            {
                                op2=s.pop();
                                op1=s.pop();
                                val=evaluate(x,op1,op2);
                                 s.push(val);
                                } 
                            } 
                            val=s.pop();
                             cout<<"\n Answer="<<val; 
                             return 0; 
                            }
 /*
  PS D:\Samiksha Gunjal> cd "d:\Samiksha Gunjal\" ; if ($?) { g++ postfix_using_stack.cpp -o postfix_using_stack } ; if ($?) { .\postfix_using_stack }
 Enter postfix Expression :52+
 Answer=7
PS D:\Samiksha Gunjal>*/
                         
                         
