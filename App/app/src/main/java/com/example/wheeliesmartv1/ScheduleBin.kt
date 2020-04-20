package com.example.wheeliesmartv1

import android.app.TimePickerDialog
import android.content.Context
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import com.google.gson.Gson
import java.io.Serializable
import java.text.SimpleDateFormat
import java.util.*



class ScheduleBin : AppCompatActivity() {

    //Custom function written to save the binList as a file on the users phone.
    fun saveData() {
        //Uses shared preferences to gain access to the users phone storage.
        val sharedPreferences =
            getSharedPreferences("shared preferences", Context.MODE_PRIVATE)
        //Edits the shared preferences.
        val editor = sharedPreferences.edit()
        //Uses Gson and Json to translate the binList into a Json file, ensuring that it can be stored and then later received.
        val gson = Gson()
        val json = gson.toJson(binList)
        editor.putString("task_list.txt", json)
        editor.apply()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_schedule_bin)
        //Receives bin from past activity.
        val newBin = intent.getSerializableExtra("newBin") as Bin
        //Sets button and other widget values.
        val mondayPickTimeBtn = findViewById<Button>(R.id.monday_btn)
        val tuesdayPickTimeBtn = findViewById<Button>(R.id.tuesday_btn)
        val wednesdayPickTimeBtn = findViewById<Button>(R.id.wednesday_btn)
        val thursdayPickTimeBtn = findViewById<Button>(R.id.thursday_btn)
        val fridayPickTimeBtn = findViewById<Button>(R.id.friday_btn)
        val saturdayPickTimeBtn = findViewById<Button>(R.id.saturday_btn)
        val sundayPickTimeBtn = findViewById<Button>(R.id.sunday_btn)
        val updateScheduleBtn = findViewById<Button>(R.id.update_schedule_btn)

        //On the update schedule button being pressed, the newBin is added to the binList and it is saved onto the users phone.
        updateScheduleBtn.setOnClickListener {
            val updateSchedule = Intent(this, ManageBins::class.java)
            updateSchedule.putExtra("newBin", newBin as Serializable)
            binList.add(newBin)
            saveData()
            startActivity(updateSchedule)

        }
        //Depending on the button; sets the newBins day to that linked to the button.
        mondayPickTimeBtn.setOnClickListener {
            newBin.day = "Monday"
        }
        tuesdayPickTimeBtn.setOnClickListener {
            newBin.day = "Tuesday"
        }
        wednesdayPickTimeBtn.setOnClickListener {
            newBin.day = "Wednesday"
        }
        thursdayPickTimeBtn.setOnClickListener {
            newBin.day = "Thursday"
        }
        fridayPickTimeBtn.setOnClickListener {
            newBin.day = "Friday"
        }
        saturdayPickTimeBtn.setOnClickListener {
            newBin.day = "Saturday"
        }
        sundayPickTimeBtn.setOnClickListener {
            newBin.day = "Sunday"
        }
    }
}

