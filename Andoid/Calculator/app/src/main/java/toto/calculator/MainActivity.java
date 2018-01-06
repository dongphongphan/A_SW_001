package toto.calculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private Button btn1,btn2,btn3,btn4,btn5,btn6,btn7,btn8,btn9,btn0,btn13,btnDot,btn20,btn19,btn18,btn17,btnDEL;
    private TextView txtResult,txtDisplay;
    private String txtInput = "" ;
    private boolean isEqual = false, isDot = false, isOperator = false, isCalculated = false;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i("LifeCycle xxxxxx", "In the onCreate() event");
        setContentView(R.layout.activity_main);
        initControlBtn();
        txtResult.setText(null);
        txtDisplay.setText(null);
        btn0.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "0");
                txtInput += "0";
                calculation();
            }
        });
        btn1.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "1");
                txtInput += "1";
                calculation();
            }});
        btn2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "2");
                txtInput += "2";
                calculation();
            }});
        btn3.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "3");
                txtInput += "3";
                calculation();}  });
        btn4.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "4");
                txtInput += "4";
                calculation();
            }});
        btn5.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "5");
                txtInput += "5";
                calculation();
            }});
        btn6.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "6");
                txtInput += "6";
                calculation();
            }});
        btn7.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "7");
                txtInput += "7";
                calculation();
            }});
        btn8.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "8");
                txtInput += "8";
                calculation();
            }});
        btn9.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isDot = false;
                isOperator = false;
                txtDisplay.setText(txtDisplay.getText() + "9");
                txtInput += "9";
                calculation();
            }});
        btnDot.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if(!isDot) {
                    txtDisplay.setText(txtDisplay.getText() + ".");
                    txtInput += ".";
                    isDot = true;
                }
            }});
        btn17.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if(!isOperator && (!txtInput.isEmpty())) {
                    isOperator = true;
                    isCalculated = true;
                    calculation();
                    txtDisplay.setText(txtDisplay.getText() + " : ");
                    txtInput += "/";
                }
                Log.i("setOnClickListener", "btn :");
            }});
        btn18.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if(!isOperator && (!txtInput.isEmpty())) {
                    isOperator = true;
                    isCalculated = true;
                    calculation();
                    txtDisplay.setText(txtDisplay.getText() + " x ");
                    txtInput += "*";
                }
                Log.i("setOnClickListener", "btn x");
            }});
        btn19.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if(!isOperator && (!txtInput.isEmpty())) {
                    isOperator = true;
                    isCalculated = true;
                    calculation();
                    txtDisplay.setText(txtDisplay.getText() + " - ");
                    txtInput += "-";
                }
            }});
        btn20.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if(!isOperator && (!txtInput.isEmpty())) {
                    isCalculated = true;
                    isOperator = true;
                    calculation();
                    txtDisplay.setText(txtDisplay.getText() + " + ");
                    txtInput += "+";
                }
                Log.i("setOnClickListener", "btn ADD");
            }});
        btnDEL.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                isOperator = false;
                isDot = false;
                isCalculated = false;
                txtDisplay.setText(null);
                txtResult.setText(null);
                txtInput = "";
                Log.i("setOnClickListener", "btn DEL");
            }});
        btn13.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if(!txtInput.isEmpty()){
                    calculation();
                    txtDisplay.setText(txtResult.getText());
                    txtInput = txtResult.getText().toString();
                    Log.i("setOnClickListener btn = ",txtInput.toString());
                    isEqual = true;
                }
            }});
    }
    private void calculation(){
        if(isCalculated){
            try{
                double result = eval(txtInput);
                String stringResult = String.format((result % 1 == 0 ? "%.0f" : "%.1f"), result);
                txtResult.setText(stringResult.toString());
            }
            catch (Exception e){
                Log.i("BACKTRACE_EVAL: ",txtInput.toString());
                txtResult.setText("Invalid expression");}
        }
    }
    private double eval(final String str) {
        return new Object() {
            int pos = -1, ch;
            void nextChar() {
                ch = (++pos < str.length()) ? str.charAt(pos) : -1;
            }
            boolean eat(int charToEat) {
                while (ch == ' ') nextChar();
                if (ch == charToEat) {
                    nextChar();
                    return true;
                }
                return false;
            }
            double parse() {
                nextChar();
                double x = parseExpression();
                if (pos < str.length()) throw new RuntimeException("Unexpected: " + (char)ch);
                return x;
            }

            // Grammar:
            // expression = term | expression `+` term | expression `-` term
            // term = factor | term `*` factor | term `/` factor
            // factor = `+` factor | `-` factor | `(` expression `)`
            //        | number | functionName factor | factor `^` factor

            double parseExpression() {
                double x = parseTerm();
                for (;;) {
                    if      (eat('+')) x += parseTerm(); // addition
                    else if (eat('-')) x -= parseTerm(); // subtraction
                    else return x;
                }
            }

            double parseTerm() {
                double x = parseFactor();
                for (;;) {
                    if      (eat('*')) x *= parseFactor(); // multiplication
                    else if (eat('/')) x /= parseFactor(); // division
                    else return x;
                }
            }

            double parseFactor() {
                if (eat('+')) return parseFactor(); // unary plus
                if (eat('-')) return -parseFactor(); // unary minus

                double x;
                int startPos = this.pos;
                if (eat('(')) { // parentheses
                    x = parseExpression();
                    eat(')');
                } else if ((ch >= '0' && ch <= '9') || ch == '.') { // numbers
                    while ((ch >= '0' && ch <= '9') || ch == '.') nextChar();
                    x = Double.parseDouble(str.substring(startPos, this.pos));
                } else if (ch >= 'a' && ch <= 'z') { // functions
                    while (ch >= 'a' && ch <= 'z') nextChar();
                    String func = str.substring(startPos, this.pos);
                    x = parseFactor();
                    if (func.equals("sqrt")) x = Math.sqrt(x);
                    else if (func.equals("sin")) x = Math.sin(Math.toRadians(x));
                    else if (func.equals("cos")) x = Math.cos(Math.toRadians(x));
                    else if (func.equals("tan")) x = Math.tan(Math.toRadians(x));
                    else throw new RuntimeException("Unknown function: " + func);
                } else {
                    throw new RuntimeException("Unexpected: " + (char)ch);
                }

                if (eat('^')) x = Math.pow(x, parseFactor()); // exponentiation

                return x;
            }
        }.parse();
    }
    private double parseString(String strNumber){
        if(strNumber != null && strNumber.length() > 0){
            try{
                return Double.parseDouble(strNumber.toString());
            }
            catch (Exception e){ Log.i("BACKTRACE_01: ",txtInput.toString());return -1;}
        }
        else return 0;
    }

    private void initControlBtn(){
        txtDisplay = (TextView)findViewById(R.id.textView);
        txtResult = (TextView)findViewById(R.id.textResult);
        btn1 = (Button)findViewById(R.id.btn1);
        btn2 = (Button)findViewById(R.id.btn2);
        btn3 = (Button)findViewById(R.id.btn3);
        btn4= (Button)findViewById(R.id.btn4);
        btn5= (Button)findViewById(R.id.btn5);
        btn6= (Button)findViewById(R.id.btn6);
        btn7= (Button)findViewById(R.id.btn7);
        btn8= (Button)findViewById(R.id.btn8);
        btn9= (Button)findViewById(R.id.btn9);
        btn0= (Button)findViewById(R.id.btn0);
        btn13 = (Button)findViewById(R.id.button13);
        btnDot = (Button)findViewById(R.id.button7);
        btnDEL= (Button)findViewById(R.id.button14);

        btn20= (Button)findViewById(R.id.button20); // +
        btn19= (Button)findViewById(R.id.button19); // -
        btn18= (Button)findViewById(R.id.button18); // x
        btn17= (Button)findViewById(R.id.button17); // /
        //btn1.setOnClickListener(onClick);
    }
    protected void onStart(){
        super.onStart();
        Log.i("LifeCycle xxxxxx", "In the onStart() event");
    }
    @Override
    protected void onPause() {
        // TODO Auto-generated method stub
        Log.i("LifeCycle xxxxxx", "In the onPause() event");
        super.onPause();
    }

    @Override
    protected void onStop() {
        // TODO Auto-generated method stub
        Log.i("LifeCycle xxxxxx", "In the onStop() event");
        super.onStop();
    }
    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        Log.i("LifeCycle xxxxxx", "In the onDestroy event");
        super.onDestroy();
    }
}
