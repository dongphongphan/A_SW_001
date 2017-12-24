package toto.calculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private Button btn1,btn2,btn3,btn4,btn5,btn6,btn7,btn8,btn9,btn0,btn13,btn20,btn19,btn18,btn17,btnDEL;
    private TextView txtResult,txtDisplay;
    private String txtInput = "" ;
    private double valueOne = Double.NaN;
    private double valueTwo;
    private static final char ADDITION = '+';
    private static final char SUBTRACTION = '-';
    private static final char MULTIPLICATION = '*';
    private static final char DIVISION = '/';
    private char CURRENT_ACTION;


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
                txtInput += "0";   }});
        btn1.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "1");
                txtInput += "1";}});
        btn2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "2");
                txtInput += "2";  }});
        btn3.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "3");
                txtInput += "3";   }  });
        btn4.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "4");
                txtInput += "4";
            }});
        btn5.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "5");
                txtInput += "5";
            }});
        btn6.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "6");
                txtInput += "6";
            }});
        btn7.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "7");
                txtInput += "7";
            }});
        btn8.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "8");
                txtInput += "8";
            }});
        btn9.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(txtDisplay.getText() + "9");
                txtInput += "9";
            }});
        btn17.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                calculation();
                txtDisplay.setText(txtDisplay.getText() + " : ");
                CURRENT_ACTION = DIVISION;
            }});
        btn18.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                calculation();
                txtDisplay.setText(txtDisplay.getText() + " x ");
                CURRENT_ACTION = MULTIPLICATION;
            }});
        btn19.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                calculation();
                txtDisplay.setText(txtDisplay.getText() + " - ");
                CURRENT_ACTION = SUBTRACTION;
            }});
        btn20.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                calculation();
                txtDisplay.setText(txtDisplay.getText() + " + ");
                CURRENT_ACTION = ADDITION;
                Log.i("setOnClickListener", "btn ADD");
            }});
        btnDEL.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                txtDisplay.setText(null);
                txtResult.setText(null);
                valueOne = Double.NaN;
                valueTwo = 0;
                Log.i("setOnClickListener", "btn DEL");
            }});
        btn13.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                calculation();
                valueTwo = 0;
            }});
    }

    private void calculation(){
        if(!Double.isNaN(valueOne))
        {
            valueTwo = parseString(txtInput.toString());
            Log.i("LOG value 1: ",Double.toString(valueOne));
            Log.i("LOG value 2: ",Double.toString(valueTwo));
            txtInput = "";
            if(CURRENT_ACTION == ADDITION){
                valueOne = this.valueOne + valueTwo;}
            else if(CURRENT_ACTION == SUBTRACTION){
                valueOne = this.valueOne - valueTwo;}
            else if(CURRENT_ACTION == MULTIPLICATION){
                valueOne = this.valueOne * valueTwo;}
            else if(CURRENT_ACTION == DIVISION){
                valueOne = this.valueOne / valueTwo;}

            txtResult.setText(Double.toString(valueOne));
        }
        else {
                try {
                    valueOne = parseString(txtInput.toString());
                    txtInput = "";
            }
            catch (Exception e){Log.i("BACKTRACE_02: ",txtInput.toString());}
        }
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
