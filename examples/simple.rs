fn main() -> Result<(), ()> {
    let value = unsafe { wrapper_rust::get_libtype() };
    println!("Obtained value : {}", value);
    let least_two = unsafe {
        wrapper_rust::sum_of_least_two(10, 20, 40)
    };
    println!("sum_of_least_two(10, 20, 40) = {}", least_two);
    return Ok(());
}
