package com.example.wheeliesmartv1
//Import the required Android and Java widgets.
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import java.io.Serializable



class BinSuccessPage : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_bin_success_page)
        //Receives new bin from previous intent.
        val newBin = intent.getSerializableExtra("newBin") as Bin
        //Sets buttons and other widgets.
        val confirmationText = findViewById<TextView>(R.id.confirmationText)
        val scheduleBtn = findViewById<Button>(R.id.scheduleBtn)
        val goBackBtn = findViewById<Button>(R.id.doneForNowBtn)

        //Changes the text to equal a preset string in Strings.xml alongside the newBin name.
        confirmationText.text = getString(R.string.placeholder_setup_confirmation_text, newBin.bName)
        //On button press bin info is stored and moved to next activity.
        scheduleBtn.setOnClickListener {
            val moveToUpdateSchedule = Intent(this, ScheduleBin::class.java)
            moveToUpdateSchedule.putExtra("newBin", newBin as Serializable)
            startActivity(moveToUpdateSchedule)
        }
        //Moves user home.
        goBackBtn.setOnClickListener {
            val moveHome = Intent(this, MainActivity::class.java)
            startActivity(moveHome)
        }
    }
}
