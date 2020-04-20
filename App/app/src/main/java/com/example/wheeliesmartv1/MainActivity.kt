package com.example.wheeliesmartv1

import android.app.Application
import android.content.Context
import android.content.Intent
import android.content.SharedPreferences
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import com.google.gson.GsonBuilder
import java.util.*
import kotlin.collections.ArrayList
import com.google.gson.reflect.TypeToken
import com.google.gson.Gson
import android.preference.PreferenceManager
import android.content.Context.MODE_PRIVATE
import java.io.*
import java.lang.reflect.Type

//Unique class for Bin object, contains String values for a name, code, and day/s. Also has an integer for its number in array.
class Bin: Serializable
{
    var bName: String = " "
    var bCode: String = " "
    var day: String = " "
    var numberInArray: Int = 0
}
//ArrayList used to store information of each bin.
var binList = ArrayList<Bin>()

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        //Uses each button on the homepage and sets them so that on trigger they change the active page using a startActivity command.
        val addNewBinBtn = findViewById<Button>(R.id.addBinBtn)
        addNewBinBtn.setOnClickListener()
        {
            val intent = Intent(this, AddNewBin::class.java)
            startActivity(intent)
        }
        val manageBinsBtn = findViewById<Button>(R.id.manageBinsBtn)
        manageBinsBtn.setOnClickListener()
        {
            val intent = Intent(this, ManageBins::class.java)
            startActivity(intent)
        }
        val settingsBtn = findViewById<Button>(R.id.settingsBtn)
        settingsBtn.setOnClickListener()
        {
            val intent = Intent(this, AddNewBin::class.java)
            startActivity(intent)
        }
    }










}
