import fitz

def fill_pdf_pymupdf(input_pdf_path, output_pdf_path, data_dict):
    doc = fitz.open(input_pdf_path)

    for page in doc:
        for field in doc.load_page(page.number).widgets():
            field_name = field.field_name
            if field_name in data_dict:
                field.field_value = data_dict[field_name]
                field.update()

    # Save the filled PDF
    doc.save(output_pdf_path, incremental=False, deflate=True)
    print(f"Filled PDF saved as '{output_pdf_path}'")

    # Flatten the PDF
    doc = fitz.open(output_pdf_path)
    for page in doc:
        page.clean_contents()  # This removes any form field interactions
    doc.save('flattened_' + output_pdf_path, deflate=True)
    print(f"Flattened PDF saved as 'flattened_{output_pdf_path}'")

# Data to fill in
data = {
    'nome': 'John Doe',
    'empresa': 'Acme Corp',
    'periodo': '2023-10'
}

# Usage
fill_pdf_pymupdf('editavel.pdf', 'filled_form.pdf', data)
