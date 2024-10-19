from PyPDF2 import PdfReader, PdfWriter

def fill_pdf(input_pdf_path, output_pdf_path, data_dict):
    reader = PdfReader(input_pdf_path)
    writer = PdfWriter()

    writer.append_pages_from_reader(reader)
    writer.update_page_form_field_values(writer.pages[0], data_dict)

    with open(output_pdf_path, 'wb') as output_stream:
        writer.write(output_stream)

# Data to fill in
data = {
    'VnQlsEiyu': 'John Doe',
    'yjtk2bp-i': 'de 2023-10-15 ate 2023-10-20',
    'xH-ZCQDmQ': 'Empresa X',
}

# Usage
fill_pdf('editavel.pdf', 'filled_form.pdf', data)
