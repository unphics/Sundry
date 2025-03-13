
fn main() {
    // 遍历resource/source目录下的所有png文件,resize到100x100,保存到resource/target目录下
    let source_dir = "./resource/source";
    let target_dir = "./resource/target";
    let files = std::fs::read_dir(source_dir).unwrap();
    for file in files {
        let file_path = file.unwrap().path();
        println!("Processing file: {:?}", file_path);
        if file_path.is_file() && file_path.to_str().unwrap().ends_with(".png") {
            let output_path = format!("{}/{}", target_dir, file_path.file_name().unwrap().to_str().unwrap());
            resize_image(&file_path.to_str().unwrap(), &output_path, 100, 100).unwrap();
        }
    }
}

fn resize_image(input_path: &str, output_path: &str, width: u32, height: u32) -> Result<(), image::ImageError> {
    println!("Input path: {}", input_path);
    println!("Output path: {}", output_path);
    let img = image::open(input_path)?;
    let resized = img.resize(width, height, image::imageops::FilterType::CatmullRom);
    resized.save(output_path)?;
    Ok(())
}
