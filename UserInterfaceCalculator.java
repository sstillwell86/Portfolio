  
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;

public class UserInterfaceCalculator extends Application {
	private MemoryCalculator calculator1 = new MemoryCalculator();
	private String operator = null;
	private Boolean equalsPressed = true;
	private Boolean operatorPressed = false;
	public TextField text = new TextField("0.0");
	@Override
	public void start(Stage primaryStage) throws Exception {
		TextField text = this.text;
		text.setFont(Font.font("Arial", FontWeight.BOLD, 20));
		text.setMinHeight(50);
		text.setMaxWidth(200);
		text.setEditable(false);
		Button bt1 = new Button("1");
		bt1.setMinWidth(50);
		bt1.setMinHeight(50);
		Button bt2 = new Button("2");
		bt2.setMinWidth(50);
		bt2.setMinHeight(50);
		Button bt3 = new Button("3");
		bt3.setMinWidth(50);
		bt3.setMinHeight(50);
		Button bt4 = new Button("4");
		bt4.setMinWidth(50);
		bt4.setMinHeight(50);
		Button bt5 = new Button("5");
		bt5.setMinWidth(50);
		bt5.setMinHeight(50);
		Button bt6 = new Button("6");
		bt6.setMinWidth(50);
		bt6.setMinHeight(50);
		Button bt7 = new Button("7");
		bt7.setMinWidth(50);
		bt7.setMinHeight(50);
		Button bt8 = new Button("8");
		bt8.setMinWidth(50);
		bt8.setMinHeight(50);
		Button bt9 = new Button("9");
		bt9.setMinWidth(50);
		bt9.setMinHeight(50);
		Button bt0 = new Button("0");
		bt0.setMinWidth(50);
		bt0.setMinHeight(50);
		Button btClear = new Button("C");
		btClear.setMinWidth(50);
		btClear.setMinHeight(50);
		Button btDivide = new Button("/");
		btDivide.setMinWidth(50);
		btDivide.setMinHeight(50);
		Button btMultiply = new Button("*");
		btMultiply.setMinWidth(50);
		btMultiply.setMinHeight(50);
		Button btSubtract = new Button("-");
		btSubtract.setMinWidth(50);
		btSubtract.setMinHeight(50);
		Button btAdd = new Button("+");
		btAdd.setMinWidth(50);
		btAdd.setMinHeight(50);
		Button btDecimal = new Button(".");
		btDecimal.setMinWidth(50);
		btDecimal.setMinHeight(50);
		Button btEquals = new Button("=");
		btEquals.setMinWidth(200);
		btEquals.setMinHeight(50);
		GridPane pane = new GridPane();
		pane.add(text, 0, 0, 4, 1);
		pane.add(bt7, 0, 1);
		pane.add(bt8, 1, 1);
		pane.add(bt9, 2, 1);
		pane.add(btDivide, 3, 1);
		pane.add(bt4, 0, 2);
		pane.add(bt5, 1, 2);
		pane.add(bt6, 2, 2);
		pane.add(btMultiply, 3, 2);
		pane.add(bt1, 0, 3);
		
		pane.add(bt2, 1, 3);
		pane.add(bt3, 2, 3);
		pane.add(btSubtract, 3, 3);
		pane.add(btClear, 0, 4);
		pane.add(bt0, 1, 4);
		pane.add(btDecimal, 2, 4);
		pane.add(btAdd, 3, 4);
		pane.add(btEquals, 0, 5);
		GridPane.setColumnSpan(btEquals, GridPane.REMAINING);
		Scene scene = new Scene(pane, 200, 300);
		primaryStage.setTitle("Calculator");
	    primaryStage.setScene(scene);
	    primaryStage.show();		 
	    
	    bt1.setOnAction(new DigitListener());
	    bt2.setOnAction(new DigitListener());
	    bt3.setOnAction(new DigitListener());
	    bt4.setOnAction(new DigitListener());
	    bt5.setOnAction(new DigitListener());
	    bt6.setOnAction(new DigitListener());
	    bt7.setOnAction(new DigitListener());
	    bt8.setOnAction(new DigitListener());
	    bt9.setOnAction(new DigitListener());
	    bt0.setOnAction(new DigitListener());
	    btDecimal.setOnAction(new DigitListener());
	    btAdd.setOnAction(new OperatorListener());
	    btSubtract.setOnAction(new OperatorListener());
	    btMultiply.setOnAction(new OperatorListener());
	    btDivide.setOnAction(new OperatorListener());
	    btClear.setOnAction(new ClearListener());
	    btEquals.setOnAction(new EqualsListener());
	}
	public static void main(String[] args) { 
	    launch(args);
	}
	
	class DigitListener implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent e) {
			Button bt = (Button) e.getSource();
			String digit = bt.getText();
			if (equalsPressed == true || operatorPressed == true) {	
				text.setText(digit);
				equalsPressed = false;
				operatorPressed = false;
			}
			else if (equalsPressed == false || operatorPressed == false) {
				text.setText(text.getText() + digit);
			}				
		}		
	}
	
	class OperatorListener implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent e) {
			Button bt =  (Button) e.getSource();
			String str = bt.getText();
			operator = str;
			calculator1.add(Double.parseDouble(text.getText()));
			operatorPressed = true;
		}
	}
	
	class ClearListener implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent e) {
			calculator1.clear();
			text.setText("0.0");
		}
	}
	class EqualsListener implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent e) {
			double operand2 = Double.parseDouble(text.getText());
			if (operator == "+") {
				calculator1.add(operand2);
			}
			else if (operator == "-") {
				calculator1.subtract(operand2);
			}
			else if (operator == "*") {
				calculator1.multiply(operand2);
			}
			else if (operator == "/") {
				calculator1.divide(operand2);
			}	
			text.setText(Double.toString(calculator1.getCurrentValue()));
			equalsPressed = true;
			operator = null;
		}	
	}
}