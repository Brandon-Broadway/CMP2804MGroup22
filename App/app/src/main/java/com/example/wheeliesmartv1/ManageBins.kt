package com.example.wheeliesmartv1

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import com.google.gson.Gson
import com.google.gson.JsonArray
import com.google.gson.reflect.TypeToken
import kotlinx.android.synthetic.main.activity_manage_bins.*
import java.io.BufferedReader
import java.io.DataOutputStream
import java.io.InputStreamReader
import java.lang.reflect.Type
import java.net.HttpURLConnection
import java.net.URL
import java.text.SimpleDateFormat

class ManageBins : AppCompatActivity() {

    //Turns an object into a byteArray
    fun objectToBytArray(ob: Any): ByteArray? {
        return ob.toString().toByteArray()
    }

    //Function to upload the binList to the Azure server.
    fun uploadBins() {
        //The servers URL is set.
        val serverURL: String = "https://aptempsensor.azurewebsites.net/api/HttpTrigger2"
        val gson = Gson()
        val url = URL(serverURL)

        val tempBin = Bin()

        //Creates a JsonArray to send to the server, and converts all the needed binData in the array into Json formatted data.
        val arrayToSend = JsonArray()
        for ((index, value) in binList.withIndex()) {
            tempBin.bName = "\\" + value.bName + "\\"
            tempBin.bCode = "\\" + value.bCode + "\\"
            tempBin.day = "\\" + value.day + "\\"

            arrayToSend.add(gson.toJson(tempBin))
        }
        //Turns JsonArray into a byteArray.
        objectToBytArray(arrayToSend)
        //Establishes connection settings.
        val connection = url.openConnection() as HttpURLConnection
        connection.requestMethod = "POST"
        connection.connectTimeout = 300000
        connection.connectTimeout = 300000
        connection.doOutput = true //Allows app to output to server.
        //Sets connection request properties.
        connection.setRequestProperty("charset", "utf-8")
        connection.setRequestProperty("Content-length", arrayToSend.toString())
        connection.setRequestProperty("Content-Type", "application/json")
        //Attempts to write the JsonArray to the server.
        try {
            val outputStream: DataOutputStream = DataOutputStream(connection.outputStream)
            outputStream.writeUTF(arrayToSend.toString())

            outputStream.flush()
        } catch (exception: Exception) {
        }
    }

    //Function to load binList from shared preferences.
    fun loadData() {
        //Uses shared preferences as before.
        val sharedPreferences =
            getSharedPreferences("shared preferences", Context.MODE_PRIVATE)
        //If the task_list.txt file has been created then it will be loaded from shared preferences, if not then nothing will happen.
        if(sharedPreferences.contains("task_list.txt")) {
            val gson = Gson()
            val json = sharedPreferences.getString("task_list.txt", null)
            //Uses a class distinction as a type token to receive the binList as both an object and a type from shared preferences.
            val type: Type = object : TypeToken<ArrayList<Bin?>?>() {}.type
            //Sets bin list to one saved in shared preferences.
            binList = gson.fromJson(json, type)
        }
        //binList.distinctBy { Pair(binList, tempList) }
    }

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
        setContentView(R.layout.activity_manage_bins)
        //Loads data from shared preferences.
        loadData()

        //Int count for setting numberInArray to its count in array.
        var intCount: Int = 0
        //String of names.
        var stringNames = ArrayList<String>()
        //For loop going through each index in bin list.
        for ((index, value) in binList.withIndex()) {
            value.numberInArray = intCount //Sets value in array to intCount and increments intCount by one to provide scaling
            intCount += 1

            stringNames.add(value.bName)

            val tvDynamic = TextView(this) //Creates new TextView that will contain the details of current index item in bin list.

            //Sets settings and contents of new Textview.
            tvDynamic.textSize = 20f
            tvDynamic.text = getString(
                R.string.bin_stats,
                value.bName,
                value.bCode,
                value.day
            )
            //Adds padding to the linearLayout and adds the new TextView into the layout.
            tvDynamic.setPadding(20, 10, 20, 10)
            ll_main_layout.addView(tvDynamic)
            //Buttons for use on screen.
            val moveHome = findViewById<Button>(R.id.homeBtn)
            val saveBins = findViewById<Button>(R.id.saveBtn)
            val removeBinBtn = findViewById<Button>(R.id.removeBinBtn)
            //Button to remove bin; if the text entered into the EditText field is the same as a bin code it uses the numberInArray integer to remove it from teh array.
            removeBinBtn.setOnClickListener {
                for ((index, value) in binList.withIndex()) {
                    if (value.bCode == binToRemove.text.toString()) {
                        binList.removeAt(value.numberInArray)
                        saveData()
                    }
                }
            }
            //Movehome button that changes the current activity.
            moveHome.setOnClickListener {
                val moveToHome = Intent(this, MainActivity::class.java)
                startActivity(moveToHome)
            }
            //Save bins button saves the current bin list and uploads it to the linked azure server.
            saveBins.setOnClickListener {
                saveData()
                uploadBins()
            }
        }
    }
}


