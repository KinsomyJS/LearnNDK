package com.kinsomy.learnndk;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.nio.Buffer;
import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity {

	private static final String TAG = "MainActivity";

	// Used to load the 'native-lib' library on application startup.
	static {
		System.loadLibrary("native-lib");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		checkPermission();
//		showDir("/storage/emulated/0/");
		// Example of a call to a native method
		TextView tv = (TextView) findViewById(R.id.sample_text);
		tv.setText(stringFromJNI());

		final Button button = findViewById(R.id.btn_jni);
		button.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				button.setText(stringFromJNI());
			}
		});
//		Log.d(TAG,Unix.getuid()+"");
		try {
			test();
		} catch (Exception e) {
			Log.e("MainActivity", "onCreate: " + e);
		}

		Bitmap bitmap = Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888);
		bitmap.eraseColor(0xff336699); // AARRGGBB
		byte[] bytes = new byte[bitmap.getWidth() * bitmap.getHeight() * 4];
		Buffer dst = ByteBuffer.wrap(bytes);
		bitmap.copyPixelsToBuffer(dst);
		// ARGB_8888 真实的存储顺序是 R-G-B-A
		Log.d(TAG, "R: " + Integer.toHexString(bytes[0] & 0xff));
		Log.d(TAG, "G: " + Integer.toHexString(bytes[1] & 0xff));
		Log.d(TAG, "B: " + Integer.toHexString(bytes[2] & 0xff));
		Log.d(TAG, "A: " + Integer.toHexString(bytes[3] & 0xff));
		passBitmap(bitmap);

	}

	/**
	 * A native method that is implemented by the 'native-lib' native library,
	 * which is packaged with this application.
	 */
	public native String stringFromJNI();

	public native void test() throws IllegalArgumentException;

	private void callNullPointerException() throws NullPointerException {
//		throw new NullPointerException("MainActivity NullPointerException");
	}

	public native void showDir(String dirPath);

	public native void passBitmap(Bitmap bitmap);

	private void checkPermission() {
		//检查权限（NEED_PERMISSION）是否被授权 PackageManager.PERMISSION_GRANTED表示同意授权
		if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
				!= PackageManager.PERMISSION_GRANTED) {
			//用户已经拒绝过一次，再次弹出权限申请对话框需要给用户一个解释
			if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission
					.WRITE_EXTERNAL_STORAGE)) {
				Toast.makeText(this, "请开通相关权限，否则无法正常使用本应用！", Toast.LENGTH_SHORT).show();
			}
			//申请权限
			ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 200);

		} else {
			Toast.makeText(this, "授权成功！", Toast.LENGTH_SHORT).show();
			Log.e("MainActivity", "checkPermission: 已经授权！");
		}
	}
}
