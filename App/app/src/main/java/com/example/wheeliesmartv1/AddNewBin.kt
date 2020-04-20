package com.example.wheeliesmartv1

import android.content.Context
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import com.google.gson.Gson
import kotlinx.android.synthetic.main.activity_add_new_bin.*
import kotlinx.android.synthetic.main.activity_manage_bins.*
import java.io.Serializable


class AddNewBin : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_new_bin)

        //Finds all buttons and EditTexts on this page and links them to a value.
        val submitBtn = findViewById<Button>(R.id.submitNewBinBtn)
        val binNameTemp = findViewById<EditText>(R.id.binName)
        val binCodeTemp = findViewById<EditText>(R.id.binCode)

        //Booleans for checking the name and code.
        var nameCheck: Boolean = false
        var codeCheck: Boolean = false

        //On button press.
        submitBtn.setOnClickListener {

            val newBin = Bin() //Newbin value.
            //If value is not default
            if(binCodeTemp.text.toString() != "Bin Code")
            {
                //Goes through each item in bin list and checks to make sure that code is not being used.
                for ((index, value) in binList.withIndex()) {
                    if (value.bCode == binCodeTemp.text.toString()) {
                        println("Please enter a valid bin name!")
                        codeCheck = true
                        break
                    }
                }
            }

            //Does the same process for the bin name.
            if(binNameTemp.text.toString() != "Bin Name")
            {
                for ((index, value) in binList.withIndex()) {
                    if (value.bName == binNameTemp.text.toString()) {
                        println("Please enter a valid bin name!")
                        nameCheck = true
                        break
                    }
                }
            }
            //As long as the appropriate booleans are false (the code and the name are not being used or default), the newBin code and name will be changed.
            if(!codeCheck)
            {
                newBin.bCode = binCodeTemp.text.toString()
            }
            if(!nameCheck)
            {
                newBin.bName = binNameTemp.text.toString()
            }
            //If both are false, then it will go to the next activity.
            if(!nameCheck && !codeCheck)
            {
                //Puts the newly created bin inside an Intent so that it andd its information can be moved throughout the application.
                val createBin = Intent(this, BinSuccessPage::class.java)
                createBin.putExtra("newBin", newBin as Serializable)
                startActivity(createBin)
            }
        }
    }
}


