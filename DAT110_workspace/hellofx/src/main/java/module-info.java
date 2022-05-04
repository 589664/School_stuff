module org.openjfx.hellofx {
    requires javafx.controls;
    requires javafx.fxml;
	requires okhttp3;
	requires com.google.gson;

    opens org.openjfx.hellofx to javafx.fxml;
    exports org.openjfx.hellofx;
}
